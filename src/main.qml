import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtQuick.Layouts 1.0
import Trans 1.0

ApplicationWindow {
    id: root
    title: qsTr("QTranslator")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open What?"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        property alias bdTranslator: bdTranslator

        GroupBox {
            title : "Inputs:"
            Layout.fillWidth: true
            TextArea {
                id: inputArea
                anchors.fill: parent
                width: parent.width
                height: parent.height
            }
        }

        RowLayout {
            id: controlRow
            width: parent.width
            height: 42
            property int site : chooseSite.currentIndex
            Label { text: "Site:" }
            ComboBox {
                id: chooseSite
                //currentIndex: 0
                model: ListModel {
                    id:siteLists
                    ListElement { text:"Baidu" }
                    ListElement { text:"Youdao" }
                }
                onCurrentIndexChanged: {
                    console.log("Site is " + siteLists.get(currentIndex).text);
                    if(currentIndex==0) {
                        //which one is better?
                        transFrom.model = Qt.binding(function() {return baiduFromLists});
                        transTo.model = baiduToLists;
                    }else if(currentIndex==1) {
                        transFrom.model = Qt.binding(function() {return youdaoFromLists});
                        transTo.model = youdaoToLists;
                    }
                    transFrom.update();
                    transTo.update();
                }

            }
            ListModel {
                id:baiduFromLists
                ListElement{modelData: "dummy"; text:"自动检测";code:"auto"}
                ListElement{modelData: "dummy"; text:"中文";code:"zh"}
                ListElement{modelData: "dummy"; text:"英语";code:"en"}
                ListElement{modelData: "dummy"; text:"粤语";code:"yue"}
                ListElement{modelData: "dummy"; text:"文言文";code:"wyw"}
                ListElement{modelData: "dummy"; text:"日语";code:"jp"}
                ListElement{modelData: "dummy"; text:"韩语";code:"kor"}
                ListElement{modelData: "dummy"; text:"法语";code:"fra"}
                ListElement{modelData: "dummy"; text:"西班牙语";code:"spa"}
                ListElement{modelData: "dummy"; text:"泰语";code:"th"}
                ListElement{modelData: "dummy"; text:"阿拉伯语";code:"ara"}
                ListElement{modelData: "dummy"; text:"俄语";code:"ru"}
                ListElement{modelData: "dummy"; text:"葡萄牙语";code:"pt"}
                ListElement{modelData: "dummy"; text:"德语";code:"de"}
                ListElement{modelData: "dummy"; text:"意大利语";code:"it"}
                ListElement{modelData: "dummy"; text:"希腊语";code:"el"}
                ListElement{modelData: "dummy"; text:"荷兰语";code:"nl"}
                ListElement{modelData: "dummy"; text:"波兰语";code:"pl"}
                ListElement{modelData: "dummy"; text:"保加利亚语";code:"bul"}
                ListElement{modelData: "dummy"; text:"爱沙尼亚语";code:"est"}
                ListElement{modelData: "dummy"; text:"丹麦语";code:"dan"}
                ListElement{modelData: "dummy"; text:"芬兰语";code:"fin"}
                ListElement{modelData: "dummy"; text:"捷克语";code:"cs"}
                ListElement{modelData: "dummy"; text:"罗马尼亚语";code:"rom"}
                ListElement{modelData: "dummy"; text:"斯洛文尼亚语";code:"slo"}
                ListElement{modelData: "dummy"; text:"瑞典语";code:"swe"}
                ListElement{modelData: "dummy"; text:"匈牙利语";code:"hu"}
                ListElement{modelData: "dummy"; text:"繁体中文";code:"cht"}
            }
            ListModel {
                id:baiduToLists
                ListElement{modelData: "dummy"; text:"中文";code:"zh"}
                ListElement{modelData: "dummy"; text:"英语";code:"en"}
                ListElement{modelData: "dummy"; text:"粤语";code:"yue"}
                ListElement{modelData: "dummy"; text:"文言文";code:"wyw"}
                ListElement{modelData: "dummy"; text:"日语";code:"jp"}
                ListElement{modelData: "dummy"; text:"韩语";code:"kor"}
                ListElement{modelData: "dummy"; text:"法语";code:"fra"}
                ListElement{modelData: "dummy"; text:"西班牙语";code:"spa"}
                ListElement{modelData: "dummy"; text:"泰语";code:"th"}
                ListElement{modelData: "dummy"; text:"阿拉伯语";code:"ara"}
                ListElement{modelData: "dummy"; text:"俄语";code:"ru"}
                ListElement{modelData: "dummy"; text:"葡萄牙语";code:"pt"}
                ListElement{modelData: "dummy"; text:"德语";code:"de"}
                ListElement{modelData: "dummy"; text:"意大利语";code:"it"}
                ListElement{modelData: "dummy"; text:"希腊语";code:"el"}
                ListElement{modelData: "dummy"; text:"荷兰语";code:"nl"}
                ListElement{modelData: "dummy"; text:"波兰语";code:"pl"}
                ListElement{modelData: "dummy"; text:"保加利亚语";code:"bul"}
                ListElement{modelData: "dummy"; text:"爱沙尼亚语";code:"est"}
                ListElement{modelData: "dummy"; text:"丹麦语";code:"dan"}
                ListElement{modelData: "dummy"; text:"芬兰语";code:"fin"}
                ListElement{modelData: "dummy"; text:"捷克语";code:"cs"}
                ListElement{modelData: "dummy"; text:"罗马尼亚语";code:"rom"}
                ListElement{modelData: "dummy"; text:"斯洛文尼亚语";code:"slo"}
                ListElement{modelData: "dummy"; text:"瑞典语";code:"swe"}
                ListElement{modelData: "dummy"; text:"匈牙利语";code:"hu"}
                ListElement{modelData: "dummy"; text:"繁体中文";code:"cht"}
            }
            ListModel {
                id: youdaoFromLists
                ListElement{modelData: "dummy"; text:"Auto";code:"auto"}
            }
            ListModel {
                id: youdaoToLists
                ListElement{modelData: "dummy";text:"中文";code:"zh"}
            }

            Label { text: "From:" }
            ComboBox {
                id: transFrom
                model: baiduFromLists
                onCurrentIndexChanged: bdTranslator.from = qsTr(transFrom.model.get(currentIndex).code)
                //console.log("From language " + fromLists.get(currentIndex).text + ". code is " + fromLists.get(currentIndex).code)
                Component.onCompleted: {
                    currentIndex = 0;
                }
            }
            Label { text: "To:" }
            ComboBox {
                id: transTo
                model:baiduToLists
                onCurrentIndexChanged: bdTranslator.to = qsTr(transTo.model.get(currentIndex).code)
                Component.onCompleted: {
                    currentIndex = 0;
                }
            }

            Button {
                id: transButton
                text: "&Trans"
                onClicked: trans()
                function trans() {
                    if(parent.site===0) {
                        bdTranslator.query = inputArea.text.toString();
                        bdTranslator.translate();
                    }else if(parent.site===1) {
                        ydTranslator.query = inputArea.text.toString();
                        ydTranslator.translate();
                    }

                }
            }
            Button {
                text: "&Clear"
                onClicked: clear()
                function clear() {
                    inputArea.remove(0,inputArea.length);
                    outputArea.remove(0,outputArea.length);
                }
            }
        }

            TextArea {
                Layout.fillWidth: true
                Layout.fillHeight: true
                id: outputArea
        }
    }


    BaiduTranslator {
        id : bdTranslator
        query: "placeholder"
        from: "auto"
        to: "zh"
        onResultChanged: outputArea.text = bdTranslator.result
    }
    YoudaoTranslator {
        id : ydTranslator
        query: "placeholder"
        onResultChanged: outputArea.text = ydTranslator.result
    }




    MessageDialog {
        id: messageDialog
        title: qsTr("Hey Notice")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

}
