import QtQuick 2.0
import QtQuick.Window 2.2
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle {

    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter {
                  name: "osm.mapping.providersrepository.disabled"
                  value: "true"
              }
              PluginParameter {
                  name: "osm.mapping.providersrepository.address"
                  value: "http://maps-redirect.qt.io/osm/5.6/"
              }
    }


    Map
    {
        id: map
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(29.7264175,55.99735)
        zoomLevel: 5
        copyrightsVisible: false
        focus: true

        MouseArea
        {
            anchors.fill: map
            hoverEnabled: true
            onPositionChanged:  {

                lat.text ="Lat :"+ map.toCoordinate(Qt.point(mouseX,mouseY)).latitude.toString()
                lon.text ="Lon :"+ map.toCoordinate(Qt.point(mouseX,mouseY)).longitude.toString()

            }

        }

        property Component itemDelegate: Component{
            Rectangle {
                width: 14
                height: 14
                radius: 7
                color: "red"
            }
        }



        MapItemView{
            id: item_view
            model: ListModel{
                id: item_model
            }
            delegate: MapQuickItem{
                id: ietm_delegate
                zoomLevel: 0
                sourceItem: Loader{
                    sourceComponent: map.itemDelegate
                }
                coordinate{
                    latitude: latitudeval
                    longitude: longitudeval
                }
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }
        }

        Rectangle
        {
            width: 251
            height: 163
            color: "#ffffff"
            border.color: "#000000"
            border.width: 1

            TextInput {
                id: textInput_x
                x: 68
                y: 25
                width: 175
                height: 30
                font.pixelSize: 16
                validator: DoubleValidator {bottom: -90.00; top: 90.00;}
                focus: true

            }

            TextInput {
                id: textInput_y
                x: 68
                y: 60
                width: 175
                height: 24
                font.pixelSize: 16
                focus: true

                validator: DoubleValidator {bottom: -90.00; top: 90.00;}
            }

            Label {
                id: label
                x: 20
                y: 25
                width: 53
                height: 30
                text: qsTr("x :")
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label1
                x: 20
                y: 60
                width: 53
                height: 30
                text: qsTr("Y :")
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                x: 8
                y: 113
                text:               "POINT Confirmed"
                Layout.fillWidth:   true

                onClicked: {
                    var waypointCoord = map.toCoordinate(Qt.point(textInput_x.text,textInput_y.text))

                    item_model.append({"latitudeval":textInput_y.text,"longitudeval":textInput_x.text});

                    console.log(waypointCoord.longitude, waypointCoord.latitude)
                }
            }
        }






        Rectangle {
            width: 206
            height: 50
            color: "white"
            anchors.top: parent.bottom
            anchors.topMargin: -50
            anchors.left: parent.right
            anchors.leftMargin: -206

            Text {
                id: lat
                width: 206
                height: 24

            }

            Text {
                id: lon
                x: 0
                y: 24
                width: 206
                height: 26

            }


        }

    }
    }





