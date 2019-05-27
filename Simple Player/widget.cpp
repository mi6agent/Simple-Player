#include "widget.h"
#include "ui_widget.h"
#include"playpauseeventwatcher.h"
#include"stopeventwatcher.h"
#include"previousnexteventwatcher.h"
#include"shuffleeventwatcher.h"
#include"repeateventwatcher.h"
#include"stylesheetsetter.h"
#include <QFileDialog>
#include <QDir>
#include<QDebug>
#include<QtWinExtras>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    StyleSheetSetter::setMainWidgetStylesheet(this);

//__________________________________________

    ui->btn_play_pause->setToolTip(tr("Play"));
    ui->btn_play_pause->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->btn_play_pause->setEnabled(false);
    PlayPauseEventWatcher *btn_play_pause_Watcher = new PlayPauseEventWatcher(this);
    ui->btn_play_pause->installEventFilter(btn_play_pause_Watcher);
    //    ui->btn_play_pause->setAutoRaise(true);
    //    ui->btn_play_pause->setFixedSize(100, 100);
    //    ui->btn_play_pause->setIconSize(QSize(100, 100));
    //    ui->btn_play_pause->setStyleSheet(toolButtonStylesheet1());

    ui->btn_next->setToolTip(tr("Play next track"));
    ui->btn_next->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->btn_next->setEnabled(false);
    PreviousNextEventWatcher *btn_next_Watcher = new PreviousNextEventWatcher(this,
                                                          ":/buttons/next-button.png",
                                                          ":/buttons/next-button-hover.png",
                                                          ":/buttons/next-button-pressed.png");
    ui->btn_next->installEventFilter(btn_next_Watcher);
//    ui->btn_next->setFixedSize(100, 100);
//    ui->btn_next->setIconSize(QSize(100, 100));
//ui->btn_next->setStyleSheet(toolButtonStylesheet());

    ui->btn_stop->setToolTip(tr("Stop"));
    ui->btn_stop->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->btn_stop->setEnabled(false);
    StopEventWatcher *btn_stop_Watcher = new StopEventWatcher(this);
    ui->btn_stop->installEventFilter(btn_stop_Watcher);
//    ButtonHoverWatcher *btn_stop_Watcher = new ButtonHoverWatcher(this,
//                                                          ":/buttons/stop-button.png",
//                                                          ":/buttons/stop-button-hover.png",
//                                                          ":/buttons/stop-button-pressed.png");
//    ui->btn_stop->installEventFilter(btn_stop_Watcher);
//    ui->btn_stop->setFixedSize(100, 100);
//    ui->btn_stop->setIconSize(QSize(100, 100));
//ui->btn_stop->setStyleSheet(toolButtonStylesheet());

    ui->btn_previous->setToolTip(tr("Play previous track"));
    ui->btn_previous->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->btn_previous->setEnabled(false);
    PreviousNextEventWatcher *btn_previous_Watcher = new PreviousNextEventWatcher(this,
                                                          ":/buttons/previous-button.png",
                                                          ":/buttons/previous-button-hover.png",
                                                          ":/buttons/previous-button-pressed.png");
    ui->btn_previous->installEventFilter(btn_previous_Watcher);
//    ui->btn_previous->setFixedSize(100, 100);
//    ui->btn_previous->setIconSize(QSize(100, 100));
//    ui->btn_previous->setStyleSheet(toolButtonStylesheet());

    ui->btn_shuffle->setToolTip(tr("Turn shuffle on"));
    ui->btn_shuffle->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ShuffleEventWatcher *btn_shuffle_Watcher = new ShuffleEventWatcher(this);
    ui->btn_shuffle->installEventFilter(btn_shuffle_Watcher);

    ui->btn_repeat->setToolTip(tr("Repeat all"));
    ui->btn_repeat->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    RepeatEventWatcher *btn_repeat_Watcher = new RepeatEventWatcher(this);
    ui->btn_repeat->installEventFilter(btn_repeat_Watcher);

    ui->btn_add->setToolTip(tr("Add tracks"));
    ui->btn_add->setStyleSheet("background-color: #64686c");
//______________________________________________________________

    //ui->volumeSlider = new QSlider(Qt::Horizontal, this);
    //    ui->volumeSlider->setRange(0, 100);
    //    ui->volumeSlider->setFixedWidth(100);
    //    ui->volumeSlider->setValue(100);

//_______________________________________________________________

    ui->currentTrack->setStyleSheet("QLabel { color : #e4e7ea; }");

    // Set up a playlist table
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);    // Set the data model in TableView
    m_playlistEmpty = true;

    // Set the table headers
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Tracks")
                                                            << tr("File Path"));

    //ui->playlistView->hideColumn(1);    // Hide the column in which the path to the file is stored
    //ui->playlistView->verticalHeader()->setVisible(false);                  // Hide the line numbering
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Enable line selection
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Let's select only one line
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Disable editing
    // Enable the fit of the last visible column size to the width of the TableView
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    ui->playlistView->setAlternatingRowColors(true);

    StyleSheetSetter::setPlayListViewStyleSheet(ui->playlistView);


    //stylize();  //stylize the main window.

    m_player = new QMediaPlayer(this);          // Initialize the player
    m_playlist = new QMediaPlaylist(m_player);  // Initialize the playlist
    m_player->setPlaylist(m_playlist);          // Set the playlist to the player
    m_player->setVolume(70);                    // Set the track playback volume
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

//_________________________________________________________________

    //Set Volume Button and Slider.
    volumeButton = new VolumeButton(this, ui->horizontalLayout_CobtrolBar);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(m_player->volume());

//________________________________________________________________

    StyleSheetSetter::setHorizontalSliderStyleSheet(ui->horizontalSlider);


//*****************************************************************

connect(m_player, &QMediaPlayer::stateChanged, [this, btn_play_pause_Watcher]()
{
    qDebug()<<"m_player state Changed to ";
    if(m_player->state() == QMediaPlayer::PlayingState)
        qDebug()<<"Playing";
    else if(m_player->state() == QMediaPlayer::PausedState)
        qDebug()<<"Paused";
    else if(m_player->state() == QMediaPlayer::StoppedState)
        qDebug()<<"stopped";

    if(!ui->btn_stop->isEnabled())
    {
        qDebug()<<"Enabling stop";
        ui->btn_stop->setEnabled(true);
    }

    if(m_player->state() == QMediaPlayer::StoppedState)
    {
        qDebug()<<"Disabling stop";
        ui->btn_stop->setEnabled(false);
        ui->btn_play_pause->setIcon(QIcon(":/buttons/play-button.png"));
        btn_play_pause_Watcher->setIsPlaying(false);
    }
    else if(m_player->state() == QMediaPlayer::PlayingState)
    {
        ui->btn_play_pause->setToolTip(tr("Pause"));
        ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/pause-button.png")));
        btn_play_pause_Watcher->setIsPlaying(true);
    }
    else if(m_player->state() == QMediaPlayer::PausedState)
    {
        ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/play-button.png")));
        ui->btn_play_pause->setToolTip(tr("Play"));
        btn_play_pause_Watcher->setIsPlaying(false);
    }
});
connect(m_playListModel, &QStandardItemModel::rowsInserted, [this]()
{
    qDebug()<<"m_playlist loaded";
    if(m_playlistEmpty)
    {
        qDebug()<<"Setting play_pause, next, previous visible";
        ui->btn_play_pause->setEnabled(true);
        ui->btn_next->setEnabled(true);
        ui->btn_previous->setEnabled(true);
        m_playlistEmpty = false;
    }
});

//______________________________________________________________________________

        // connect the control buttons to the control slots
         // Here it is noted that navigation through the playlist is performed through the playlist
         // and start / pause / stop through the player itself
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_play_pause, &QToolButton::clicked, [this](){
        qDebug()<<"btn_play_pause clicked";
        if (m_player->state() == QMediaPlayer::PlayingState)
            m_player->pause();
        else
            m_player->play();
    });
/*    connect(m_player, &QMediaPlayer::stateChanged, [this](){
        if(m_player->state() == QMediaPlayer::PlayingState)
            ui->btn_play_pause->setToolTip(tr("Pause"));
        else
        {
            ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/play-button.png")));
            ui->btn_play_pause->setToolTip(tr("Play"));
        }
    });*/
    connect(ui->btn_stop, &QToolButton::clicked, [this]()
    {
        qDebug()<<"Stop clicked";
//        if(m_player->state() == QMediaPlayer::PlayingState)
//            ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/play-button.png")));
        m_player->stop();
    });
    connect(ui->btn_repeat, &QToolButton::clicked, [this, btn_repeat_Watcher]()
    {
        qDebug()<<"Repeat clicked";
        if(btn_repeat_Watcher->getRepeatMode() == QMediaPlaylist::Sequential)
        {
            m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
            qDebug()<<"Repeat mode changed to Sequential";
        }
        else if(btn_repeat_Watcher->getRepeatMode() == QMediaPlaylist::Loop)
        {
            m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
            qDebug()<<"Repeat mode changed to Loop";
        }
        else
        {
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            qDebug()<<"Repeat mode changed to CurrentItemInLoop";
        }
     });


    connect(volumeButton, &VolumeButton::volumeChanged, m_player, &QMediaPlayer::setVolume);  //Connect volume slider to media player

    // With a double click on a track in the table, set the track in the playlist
    connect(ui->playlistView, &QTableView::doubleClicked, [this, btn_play_pause_Watcher](const QModelIndex &index)
    {
        m_playlist->setCurrentIndex(index.row());
        ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/pause-button.png")));
        m_player->play();
        btn_play_pause_Watcher->setIsPlaying(true);
    });


    //connect(m_player, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(onMetaDataAvailable(bool)));

//    connect(m_player, &QMediaPlayer::mediaStatusChanged, [this]()
//    {
//       qDebug()<<m_player->mediaStatus();

//       if(m_player->mediaStatus()==QMediaPlayer::BufferedMedia)
//       {
//           qDebug()<<m_player->metaData(QMediaMetaData::Title).toString();
//           ui->currentTrack->setText(m_player->metaData("Title").toString()+tr("\n")+m_player->metaData("AudioBitRate").toString());
//       }

//    });

//     when changing the index of the current track in the playlist, set the file name in a special label

    connect(m_player, &QMediaPlayer::durationChanged, [this, btn_shuffle_Watcher](){
        qDebug().noquote()<<"duration = "<<m_player->duration()<<" "<<m_player->duration()/1000;
        ui->horizontalSlider->setRange(0, (m_player->duration()/1000 + 1) * 2);
        //qDebug().noquote()<<"Seconds part of Total length: "<<(m_player->duration()/1000)%60;

        QString data;
        QTextStream out(&data);
              out << m_player->duration()/1000/60 << ":" << qSetFieldWidth(2) << right <<qSetPadChar('0')<< (m_player->duration()/1000)%60;
        ui->trackTotalTime->setText(data);

        if(btn_shuffle_Watcher->statusOn())
            m_playlist->shuffle();

         ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(m_playlist->currentIndex(), 0)).toString());

        //**********************************



        //ui->trackTotalTime->setText(QString().asprintf("%d:%2d", m_player->duration()/1000/60, (int)((m_player->duration()/1000)%60)));

        //qDebug().noquote()<<"trackTime W = "<<ui->trackTime->width()<<" H = "<<ui->trackTime->height();
        //ui->progressBar->reset();
    });

    connect(m_player, &QMediaPlayer::positionChanged, [this](){
                //ui->progressBar->show();
                qDebug().noquote()<<"positon = "<<m_player->position();
                ui->horizontalSlider->setValue((m_player->position()/1000) * 2);
                fillAudioTimeInfo(m_player->position());
                showTrackTime();
            });


    connect(ui->horizontalSlider, &QSlider::sliderReleased, [this, btn_play_pause_Watcher](){
        if(sliderValueChanged)
        {
            seek(ui->horizontalSlider->value());
            sliderValueChanged = false;
        }
        if(btn_play_pause_Watcher->getIsPlaying())
            m_player->play();
        m_player->blockSignals(false);
    });
    connect(ui->horizontalSlider, &QSlider::sliderPressed, [this](){
        m_player->blockSignals(true);
        if(m_player->state() == QMediaPlayer::PlayingState)
            m_player->pause();
        //ui->horizontalSlider->setStatusTip(QString().asprintf("%d:%02d", audioTime[0], audioTime[1]));
    });
    connect(ui->horizontalSlider, &QSlider::sliderMoved, [this](){
        sliderValueChanged = true;
        fillAudioTimeInfo(ui->horizontalSlider->value()*500);
        showTrackTime();
    });

    createTaskbar();
    createThumbnailToolBar();
}

Widget::~Widget()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}

void Widget::on_btn_add_clicked()
{
    // Use the file selection dialog to make multiple selections of mp3 files
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString("C:/Users/HP/Music"),
                                                      tr("Audio Files (*.mp3)"));

    // Next we set the data by the names and paths to the files
         // into a playlist and a table displaying a playlist
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}

//_______________________________________________________________


void Widget::seek(int value)
{
    m_player->setPosition((value / 2) * 1000);
}

//QString Widget::toolButtonStylesheet()
//{
//    return QString("QToolButton {\
//                   border: 2px solid #8f8f91;\
//                   border-radius: 6px;\
//                   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
//                                                     stop: 0 #f6f7fa, stop: 1 #dadbde);\
//                   min-width: 80px;\
//               }\
//               \
//               QToolButton:pressed {\
//                   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
//                                                     stop: 0 #dadbde, stop: 1 #f6f7fa);\
//               }\
//               \
//               QToolButton:flat {\
//                   border: none; /* no border for a flat push button */\
//               }\
//               \
//               QToolButton:default {\
//                   border-color: navy; /* make the default button prominent */\
//               }\
//               ");
//}


//                   "QToolButton {\n"
//                                      "   border: none;\n"
//                                      "   background: url(:/buttons/icon.png) top center no-repeat;\n"
//                                      "   padding-top: 200px;\n"
//                                      "   width: 200px;\n"
//                                      "   font: bold 14px;\n"
//                                      "   color: red;\n"
//                                      "}\n"
//                                      "QToolButton:hover {\n"
//                                      "   background: url(:/buttons/play-button -hover.png) top center no-repeat;\n"
//                                      "   color: blue;\n"
//                                      "}\n"
//                                      "QToolButton:pressed {\n"
//                                      "   background: url(:/buttons/play-button-pressed.png) top center no-repeat;\n"
//                                      "   color: gray;\n}"

void Widget::fillAudioTimeInfo(int playerPosition)
{
    audioTime[0] = playerPosition/1000/60;
    audioTime[1] = (playerPosition/1000)%60;
}

void Widget::showTrackTime()
{
    ui->trackTime->setText(QString().asprintf("%d:%02d", audioTime[0], audioTime[1]));
}

void Widget::createTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());

    taskbarProgress = taskbarButton->progress();
    connect(ui->horizontalSlider, &QAbstractSlider::valueChanged, taskbarProgress, &QWinTaskbarProgress::setValue);
    connect(ui->horizontalSlider, &QAbstractSlider::rangeChanged, taskbarProgress, &QWinTaskbarProgress::setRange);
    connect(m_player, &QMediaPlayer::stateChanged, this, &Widget::updateTaskbar);
}

void Widget::updateTaskbar()
{
    switch (m_player->state()) {
    case QMediaPlayer::PlayingState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        taskbarProgress->show();
        taskbarProgress->resume();
        break;
    case QMediaPlayer::PausedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPause));
        taskbarProgress->show();
        taskbarProgress->pause();
        break;
    case QMediaPlayer::StoppedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaStop));
        taskbarProgress->hide();
        break;
    }
}

void Widget::createThumbnailToolBar()
{
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    thumbnailToolBar->setWindow(windowHandle());

    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    playToolButton->setEnabled(false);
    playToolButton->setToolTip(tr("Play"));
    playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playToolButton, &QWinThumbnailToolButton::clicked, this, &Widget::togglePlayback);

    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    forwardToolButton->setEnabled(false);
    forwardToolButton->setToolTip(tr("Next"));
    forwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    connect(forwardToolButton, &QWinThumbnailToolButton::clicked, m_playlist, &QMediaPlaylist::next);

    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    backwardToolButton->setEnabled(false);
    backwardToolButton->setToolTip(tr("Previous"));
    backwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    connect(backwardToolButton, &QWinThumbnailToolButton::clicked, m_playlist, &QMediaPlaylist::previous);

    thumbnailToolBar->addButton(backwardToolButton);
    thumbnailToolBar->addButton(playToolButton);
    thumbnailToolBar->addButton(forwardToolButton);

    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::updateThumbnailToolBar);
    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::updateThumbnailToolBar);

    connect(m_player, &QMediaPlayer::stateChanged, this, &Widget::updateThumbnailToolBar);
}

void Widget::updateThumbnailToolBar()
{
    playToolButton->setEnabled(m_player->duration() > 0);
    backwardToolButton->setEnabled(m_player->duration()> 0);
    forwardToolButton->setEnabled(m_player->position() < m_player->duration());

    if (m_player->state() == QMediaPlayer::PlayingState) {
        playToolButton->setToolTip(tr("Pause"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        playToolButton->setToolTip(tr("Play"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void Widget::togglePlayback()
{
    if (m_player->mediaStatus() == QMediaPlayer::NoMedia)
        on_btn_add_clicked();
    else if (m_player->state() == QMediaPlayer::PlayingState)
        m_player->pause();
    else
        m_player->play();
}

void Widget::seekForward()
{
    m_playlist->next();
    //ui->horizontalSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void Widget::seekBackward()
{
    m_playlist->previous();
    //ui->horizontalSlider->triggerAction(QSlider::SliderPageStepSub);
}

//void Widget::onMetaDataAvailable(bool available)
//{
//   if (available)
//       qDebug()<<m_player->metaData(QMediaMetaData::Title).toString();
//};

//void Widget::onPlayPauseClicked(){
//    qDebug()<<"btn_play_pause clicked";
//    if(m_player->state() == QMediaPlayer::PausedState || m_player->state() == QMediaPlayer::StoppedState) //&& m_playListModel->rowCount())
//    {
//        //ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/pause-button.png")));
//        ui->btn_play_pause->setToolTip(tr("Pause"));
//        m_player->play();
//    }
//    else
//    {
//        //ui->btn_play_pause->setIcon(QIcon(QPixmap(":/buttons/play-button.png")));
//        ui->btn_play_pause->setToolTip(tr("Play"));
//        m_player->pause();
//    }
//}
