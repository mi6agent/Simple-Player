#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include"volumebutton.h"

QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolBar)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolButton)

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createThumbnailToolbar();
    void updateThumbnailToolbar();
    void stylize();
    ~Widget();

public slots:                   //************
    void togglePlayback();
    void seekForward();
    void seekBackward();

private slots:
    void on_btn_add_clicked();           // Slot for processing the addition of tracks through the dialog box
    void seek(int value);
//    void onPlayPauseClicked();

    void updateTaskbar();                   //**********
    void updateThumbnailToolBar();

private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;   // Playlist data model for display
    QMediaPlayer        *m_player;          // Track Player
    QMediaPlaylist      *m_playlist;        // Playlist Producer
    VolumeButton *volumeButton;
    bool m_playlistEmpty;

    bool sliderValueChanged;
    int audioTime[2];

    QWinTaskbarButton *taskbarButton = nullptr;             //***************
    QWinTaskbarProgress *taskbarProgress = nullptr;
    QWinThumbnailToolBar *thumbnailToolBar = nullptr;
    QWinThumbnailToolButton *playToolButton = nullptr;
    QWinThumbnailToolButton *forwardToolButton = nullptr;
    QWinThumbnailToolButton *backwardToolButton = nullptr;

    void takePlayPauseStopAction();
    QString toolButtonStylesheet();

    void fillAudioTimeInfo(int playerPosition);
    void showTrackTime();

    void createTaskbar();                                  //***********
    void createThumbnailToolBar();
};

#endif // WIDGET_H
