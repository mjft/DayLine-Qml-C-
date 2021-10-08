import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import Qt5Compat.GraphicalEffects


import QtQuick.Layouts 1.3


Window{
//最底层透明图层
id:mainWindow
visible:true
width: 200
height: 850
flags: Qt.Window | Qt.FramelessWindowHint//去掉原始标题栏
color: "transparent"
property int listViewActive: 0
property bool isTop:false

Item {
    id: item1
    anchors.centerIn: parent;
    width: parent.width
    height: parent.height
    Rectangle {
        id:mainRect
        anchors.centerIn: parent;
        width: parent.width-20
        height: parent.height-20





         //头栏
         Rectangle {
             id: title
             anchors.top: mainRect.top
             width: mainRect.width
             height: 30
             color: "#979797"

             //头栏拖动
             MouseArea {
                 anchors.fill: parent
                 acceptedButtons: Qt.LeftButton
                 property point clickPos: "0,0"
                 onPressed: {
                     clickPos = Qt.point(mouse.x, mouse.y)
                 }
                 onPositionChanged: {
                     //鼠标偏移量
                     var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                     //如果mainwindow继承自QWidget,用setPos
                     mainWindow.setX(mainWindow.x + delta.x)
                     mainWindow.setY(mainWindow.y + delta.y)
                 }
             }

             //关闭按钮
             Button {
                 id: closeButton
                 anchors.right: title.right
                 width: 30
                 height: 30
                 Rectangle{
                     anchors.fill : parent
                     color:title.color
                 }
                 //图标
                 Image {
                     id:closepng
                     width: 20
                     height: 20
                     anchors.centerIn: parent
                     //按钮两态
                     source:{
                         if(closeButton.hovered)//指针悬浮时
                         {"/DayLine/png/close2.png"}
                         else{"/DayLine/png/close.png"}//指针未进入按钮
                     }
                     fillMode: Image.PreserveAspectFit
                     smooth:             true
                     antialiasing:       true
                 }
                 MouseArea{
                     anchors.fill: parent
                     onClicked: {
                         Qt.quit()//退出程序
                     }
                 }
             }

             }

         Rectangle{
             anchors.top: title.bottom
             anchors.left: mainRect.left
             anchors.right: mainRect.right
             anchors.bottom: mainRect.bottom
             //提供一个较小的视窗,显示一个较大的内容,内容可在这个小视窗中进行拖动
             Flickable {
                 id: myflick
                 anchors.fill: parent
                 contentHeight:png1.height
                 flickableDirection :Flickable.VerticalFlick //只允许垂直操作
                 boundsBehavior :Flickable.StopAtBounds //内容不能被拖出视窗边界，轻拂时内容也不会超出视窗边界
                 clip: true //不在指定区域外显示
                 Image {
                     id: png1
                     anchors.top: parent.top
                     anchors.right: parent.right
                     width: title.width
                     height: 800
                     fillMode: Image.Stretch
                     source: "/DayLine/png/line.png"
                 }
                 Image {
                     id: png1200
                     x:0
                     y:5 * parent.height / 12
                     width: 80
                     height: 40
                     fillMode: Image.Stretch
                     source: "/DayLine/png/1200.png"
                 }
                 Image {
                     id: png1100
                     x:0
                     y:6 * parent.height / 12
                     width: 80
                     height: 40
                     fillMode: Image.Stretch
                     source: "/DayLine/png/1100.png"
                 }
                 Image {
                     id: png1000
                     x:0
                     y:7 * parent.height / 12
                     width: 80
                     height: 40
                     fillMode: Image.Stretch
                     source: "/DayLine/png/1000.png"
                 }
                 //图片长度拉伸（拉伸image长度），放在flickable里才能同时实现拖动和鼠标缩放
                 MouseArea{
                     anchors.fill: parent
                     onWheel: {
                         //每次滚动都是120的倍数
                         var datla = wheel.angleDelta.y/120;
                         if(datla > 0)
                         {
                             png1.height = png1.height * 1.2
                             myflick.contentY = myflick.contentY + 0.2 * wheel.y
                         }
                         else
                         {
                             png1.height = png1.height * 0.8
                             myflick.contentY = myflick.contentY - 0.2 * wheel.y
                         }
                         if(png1.height < 800)
                         {
                             png1.height = 800
                         }
                     }
                 }
             }

         }
    }
}

DropShadow {//绘制阴影
        id: rectShadow;
        anchors.fill: source
        //cached: true;
        horizontalOffset: 0;
        verticalOffset: 0;
        radius: 8.0;
        //samples: 17;
        //spread: 0.0
        color: "#80000000";
        //smooth: true;
        source: item1;
}

}
