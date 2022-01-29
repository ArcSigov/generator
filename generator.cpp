#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s)),
    manager(new TblFileManager(this)),
    interpreter(new TblDataInterpreter(&s,this))
{
    //!< обработчик события загрузки таблицы
    //! 1. По нажатию на кнопку "открыть" из диалогового окна возвращается путь к файлу
    //! 2. Путь к файлу приходит в объект чтения файлов, который формирует контейнер строк для дальнейшего анализа данных
    //! 3. Контейнер для анализа передается в интерпретатор данных, который формирует структуру хранилища
    //! 4. Интерпретатор уведомляет объекты о готовности данных для их отображения и обработки
    connect(window,&MainWindow::filePathSetted,manager,&FileManager::readFile);
    connect(manager,&FileManager::readResult,interpreter,&FileDataInterpreter::readFileData);
    connect(interpreter,&FileDataInterpreter::dataFromFileCompleted,window,&MainWindow::updateTable);

    //!< обработчик события сохранения таблицы
    //! 1. Обработчик окна направляет в файловый менеджер путь к файлу сохранения
    //! 2. Если путь валиден, то файловый менеджер запрашивает интерпретатор подготовить ему данные на отправку
    //! 3. Подготовив данные, файловый интерпретатор передает их файловому менеджеру на сохранение
    connect(window,&MainWindow::saveFilePath,manager,&FileManager::setFilePath);
    connect(manager,&FileManager::getDataToWrite,interpreter,&FileDataInterpreter::interpreteToFileData);
    connect(interpreter,&FileDataInterpreter::dataToFileCompleted,manager,&FileManager::writeToFile);
    connect(manager,&FileManager::saveResult,window,&MainWindow::showSaveFileResult);
    window->show();
}

Generator::~Generator()
{
    delete window;
}

