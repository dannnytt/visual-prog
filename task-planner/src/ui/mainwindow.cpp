#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupDatabase();
    loadTasksFromDatabase();
}

MainWindow::~MainWindow() {
    saveTasksToDatabase();
}

void MainWindow::setupUI() {
    showMaximized();

    // Настройки сплиттера
    splitter = new QSplitter(Qt::Horizontal, this);

    // Настройки интерфейса
    setupMiddlePart();
    setupRightPart();

    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 1);


    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(splitter);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkTaskDeadlines);
    timer->start(60000); // Запускаем таймер для проверки каждую минуту (60000 мс)
}

void MainWindow::setupMiddlePart() {
    QGroupBox *middleGroup = new QGroupBox(this);
    QGridLayout *middleLayout = new QGridLayout(middleGroup);

    taskList = new QListWidget(this);
    completedTaskList = new QListWidget(this);
    addTaskButton = new QPushButton("Добавить задачу", this);
    removeTaskButton = new QPushButton("Удалить задачу", this);
    editTaskButton = new QPushButton("Изменить задачу");

    middleLayout->addWidget(addTaskButton, 0, 0, 1, 2);
    middleLayout->addWidget(removeTaskButton, 1, 0);
    middleLayout->addWidget(editTaskButton, 1, 1);
    middleLayout->addWidget(taskList, 2, 0, 1, 2);
    middleLayout->addWidget(completedTaskList, 3, 0, 1, 2);
    middleGroup->setLayout(middleLayout);
    splitter->addWidget(middleGroup);

    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(removeTaskButton, &QPushButton::clicked, this, &MainWindow::removeTask);
    connect(editTaskButton, &QPushButton::clicked, this, [this]() {
        editTask(taskList->currentItem());
    });
    connect(taskList, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);

    // Обработчик для изменения состояния чекбокса
    connect(taskList, &QListWidget::itemChanged, this, &MainWindow::completeTask);
    connect(completedTaskList, &QListWidget::itemChanged, this, &MainWindow::removeCompletedTask);
}

void MainWindow::setupRightPart() {
    QGroupBox *rightGroup = new QGroupBox(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightGroup);

    // Метки для деталей задачи
    nameLabel = new QLabel("Название задачи:", this);
    themeLabel = new QLabel("Тема задачи:", this);
    deadlineLabel = new QLabel("Срок:", this);
    priorityLabel = new QLabel("Приоритет:", this);
    subtasksListWidget = new QListWidget(this);
    subtasksListWidget->setObjectName("subtasksListWidget");

    // Создаем QFrames для разделителей
    QFrame *frame1 = new QFrame(this);
    frame1->setFrameShape(QFrame::HLine);
    frame1->setFrameShadow(QFrame::Sunken);

    QFrame *frame2 = new QFrame(this);
    frame2->setFrameShape(QFrame::HLine);
    frame2->setFrameShadow(QFrame::Sunken);

    QFrame *frame3 = new QFrame(this);
    frame3->setFrameShape(QFrame::HLine);
    frame3->setFrameShadow(QFrame::Sunken);

    QFrame *frame4 = new QFrame(this);
    frame4->setFrameShape(QFrame::HLine);
    frame4->setFrameShadow(QFrame::Sunken);

    // Добавляем метки и разделители в layout
    rightLayout->addWidget(nameLabel);
    rightLayout->addWidget(frame1); // Разделитель между метками
    rightLayout->addWidget(themeLabel);
    rightLayout->addWidget(frame2); // Разделитель между метками
    rightLayout->addWidget(deadlineLabel);
    rightLayout->addWidget(frame3); // Разделитель между метками
    rightLayout->addWidget(priorityLabel);

    // Добавляем разделитель перед списком подзадач
    rightLayout->addWidget(frame4); // Новый разделитель


    // Настраиваем subtasksListWidget как растягивающийся элемент
    rightLayout->addWidget(new QLabel("Подзадачи", this));
    rightLayout->addWidget(subtasksListWidget);
    rightLayout->addStretch(1); // Добавляем пружину для растягивания списка

    rightGroup->setLayout(rightLayout);
    splitter->addWidget(rightGroup);

    // Подключение сигнала currentRowChanged к обновлению деталей задачи
    connect(taskList, &QListWidget::currentRowChanged, this, &MainWindow::showTaskDetails);
}


void MainWindow::addTask() {
    TaskDialog dialog(this);
    dialog.setWindowTitle(tr("Добавление задачи"));
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString theme = dialog.getGroup(); // Получаем тему
        QDate deadline = dialog.getDeadline();
        int priority = dialog.getPriority();
        QStringList subtasks = dialog.getSubtasks();

        QListWidgetItem *taskItem = new QListWidgetItem(name, taskList);
        taskItem->setFlags(taskItem->flags() | Qt::ItemIsUserCheckable);
        taskItem->setCheckState(Qt::Unchecked);

        taskItem->setData(Qt::UserRole + 1, theme);     // Сохраняем тему
        taskItem->setData(Qt::UserRole + 2, deadline);
        taskItem->setData(Qt::UserRole + 3, priority);
        taskItem->setData(Qt::UserRole + 4, QVariant(subtasks));

        taskList->addItem(taskItem);
    }
}


void MainWindow::removeTask() {
    int index = taskList->currentRow();
    if (index >= 0) {
        delete taskList->takeItem(index);
    }
}

void MainWindow::editTask(QListWidgetItem *item) {
    if (!item) return;

    QString currentName = item->text();
    QString currentTheme = item->data(Qt::UserRole + 1).toString(); // Тема
    QDate currentDeadline = item->data(Qt::UserRole + 2).toDate();
    int currentPriority = item->data(Qt::UserRole + 3).toInt();
    QStringList currentSubtasks = item->data(Qt::UserRole + 4).toStringList();

    TaskDialog dialog(this);
    dialog.setWindowTitle(tr("Редактирование задачи"));
    dialog.setName(currentName);
    dialog.setGroup(currentTheme); // Устанавливаем текущую тему
    dialog.setDeadline(currentDeadline);
    dialog.setPriority(currentPriority);
    dialog.setSubtasks(currentSubtasks);

    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.getName();
        QString newTheme = dialog.getGroup(); // Получаем новую тему
        QDate newDeadline = dialog.getDeadline();
        int newPriority = dialog.getPriority();
        QStringList newSubtasks = dialog.getSubtasks();

        if (!newName.isEmpty() && newName != currentName) {
            item->setText(newName);
        }

        item->setData(Qt::UserRole + 1, newTheme);    // Обновляем тему
        item->setData(Qt::UserRole + 2, newDeadline);
        item->setData(Qt::UserRole + 3, newPriority);
        item->setData(Qt::UserRole + 4, QVariant(newSubtasks));
    }
}


void MainWindow::completeTask(QListWidgetItem *item) {
    if (!item) return;

    if (item->checkState() == Qt::Checked) {
        QListWidgetItem *completedItem = taskList->takeItem(taskList->row(item));
        completedTaskList->addItem(completedItem);
        completedItem->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::removeCompletedTask(QListWidgetItem *item ) {
    if (!item) return;

    if (item->checkState() == Qt::Checked) {
        delete completedTaskList->takeItem(completedTaskList->row(item));
    }
}

void MainWindow::showTaskDetails(int index) {
    if (index >= 0) {
        QListWidgetItem *item = taskList->item(index);

        QString taskName = item->text();
        QString taskTheme = item->data(Qt::UserRole + 1).toString(); // Тема
        QDate taskDeadline = item->data(Qt::UserRole + 2).toDate();
        int taskPriority = item->data(Qt::UserRole + 3).toInt();
        QStringList taskSubtasks = item->data(Qt::UserRole + 4).toStringList();

        nameLabel->setText("Название задачи: " + taskName);
        themeLabel->setText("Тема задачи: " + taskTheme); // Обновляем метку темы
        deadlineLabel->setText("Срок: " + taskDeadline.toString());
        priorityLabel->setText("Приоритет: " + priorityToString(taskPriority));

        subtasksListWidget->clear();
        for (const QString &subtask : taskSubtasks) {
            subtasksListWidget->addItem(subtask);
        }
    } else {
        nameLabel->clear();
        themeLabel->clear(); // Очищаем метку темы
        deadlineLabel->clear();
        priorityLabel->clear();
        subtasksListWidget->clear();
    }
}


// Function to convert priority integer to string
QString MainWindow::priorityToString(int priority) {
    switch (priority) {
    case 1: return "Низкий";
    case 2: return "Средний";
    case 3: return "Высокий";
    default: return "Неизвестно";
    }
}

void MainWindow::setupDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");
    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "theme TEXT, "
                    "deadline TEXT, "
                    "priority INTEGER, "
                    "subtasks TEXT, "
                    "completed INTEGER)")) {
        qDebug() << "Error: Failed to create table - " << query.lastError().text();
    }

    db.close(); // Close the database connection after setup
}

void MainWindow::saveTasksToDatabase() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Error: Unable to open database!";
        return;
    }

    QSqlQuery query;
    query.exec("DELETE FROM tasks"); // Clear table before saving

    // Save non-completed tasks
    for (int i = 0; i < taskList->count(); ++i) {
        QListWidgetItem *item = taskList->item(i);
        query.prepare("INSERT INTO tasks (name, theme, deadline, priority, subtasks, completed) "
                      "VALUES (:name, :theme, :deadline, :priority, :subtasks, :completed)");
        query.bindValue(":name", item->text());
        query.bindValue(":theme", item->data(Qt::UserRole + 1).toString());
        query.bindValue(":deadline", item->data(Qt::UserRole + 2).toDate().toString(Qt::ISODate));
        query.bindValue(":priority", item->data(Qt::UserRole + 3).toInt());
        query.bindValue(":subtasks", item->data(Qt::UserRole + 4).toStringList().join(";"));
        query.bindValue(":completed", 0); // Not completed
        if (!query.exec()) {
            qDebug() << "Error: Failed to save task - " << query.lastError().text();
        }
    }

    // Save completed tasks
    for (int i = 0; i < completedTaskList->count(); ++i) {
        QListWidgetItem *item = completedTaskList->item(i);
        query.prepare("INSERT INTO tasks (name, theme, deadline, priority, subtasks, completed) "
                      "VALUES (:name, :theme, :deadline, :priority, :subtasks, :completed)");
        query.bindValue(":name", item->text());
        query.bindValue(":theme", item->data(Qt::UserRole + 1).toString());
        query.bindValue(":deadline", item->data(Qt::UserRole + 1).toDate().toString(Qt::ISODate));
        query.bindValue(":priority", item->data(Qt::UserRole + 2).toInt());
        query.bindValue(":subtasks", item->data(Qt::UserRole + 3).toStringList().join(";"));
        query.bindValue(":completed", 1); // Completed
        if (!query.exec()) {
            qDebug() << "Error: Failed to save completed task - " << query.lastError().text();
        }
    }

    db.close(); // Close the database connection after saving tasks
}

void MainWindow::loadTasksFromDatabase() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Error: Unable to open database!";
        return;
    }

    QSqlQuery query("SELECT name, theme, deadline, priority, subtasks, completed FROM tasks");

    while (query.next()) {
        QListWidgetItem *item = new QListWidgetItem(query.value(0).toString());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(query.value(5).toBool() ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole + 1, query.value(1).toString()); // Store theme
        item->setData(Qt::UserRole + 2, QDate::fromString(query.value(2).toString(), Qt::ISODate)); // Store deadline
        item->setData(Qt::UserRole + 3, query.value(3).toInt()); // Store priority
        item->setData(Qt::UserRole + 4, query.value(4).toString().split(";")); // Store subtasks

        if (query.value(5).toBool()) {
            completedTaskList->addItem(item);
        } else {
            taskList->addItem(item);
        }
    }

    db.close(); // Close the database connection after loading tasks
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveTasksToDatabase();
    QMainWindow::closeEvent(event);
}

void MainWindow::checkTaskDeadlines() {
    QDate currentDate = QDate::currentDate();

    // Проверяем сроки задач в taskList
    for (int i = 0; i < taskList->count(); ++i) {
        QListWidgetItem *item = taskList->item(i);
        QDate deadline = item->data(Qt::UserRole + 1).toDate();

        if (currentDate >= deadline) {
            showNotification(item->text());
        }
    }
}

void MainWindow::showNotification(const QString &taskName) {
    QMessageBox::information(this, "Напоминание", "Задача \"" + taskName + "\" должна быть выполнена.");
}
