/*
 *   SPDX-FileCopyrightText: 2015 Aleix Pol Gonzalez <aleixpol@blue-systems.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQml.Models 2.15
import org.kde.discover 2.0
import org.kde.discover.app 1.0
import "navigation.js" as Navigation
import org.kde.kirigami 2.14 as Kirigami

DiscoverPage
{
    id: page
    title: i18n("Featured")
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0

    actions.main: searchAction

    readonly property bool isHome: true

    function searchFor(text) {
        if (text.length === 0)
            return;
        Navigation.openCategory(null, "")
    }

    ColumnLayout {
        anchors.centerIn: parent
        opacity: 0.5

        visible: featureCategory.count === 0 && featureCategory.model.isFetching

        Kirigami.Heading {
            level: 2
            Layout.alignment: Qt.AlignCenter
            text: i18n("Loading…")
        }
        BusyIndicator {
            id: indicator
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Kirigami.Units.gridUnit * 4
            Layout.preferredHeight: Kirigami.Units.gridUnit * 4
        }
    }

    Kirigami.PlaceholderMessage {
        anchors.centerIn: parent
        width: parent.width - (Kirigami.Units.largeSpacing * 4)

        visible: featureCategory.count === 0 && !featureCategory.model.isFetching

        icon.name: "network-disconnect"
        text: i18n("Unable to load applications")
        explanation: i18n("Please verify Internet connectivity")
    }

    signal clearSearch()

    readonly property bool compact: page.width < 550 || !applicationWindow().wideScreen

    footer: ColumnLayout {
        spacing: 0

        Kirigami.Separator {
            Layout.fillWidth: true
            visible: Kirigami.Settings.isMobile && inlineMessage.visible
        }

        Kirigami.InlineMessage {
            id: inlineMessage
            icon.name: updateAction.icon.name
            showCloseButton: true
            Layout.fillWidth: true
            Layout.margins: Kirigami.Units.largeSpacing * 2
            text: i18n("Updates are available")
            visible: Kirigami.Settings.isMobile && ResourcesModel.updatesCount > 0
            actions: Kirigami.Action {
                icon.name: "go-next"
                text: i18nc("Short for 'show updates'", "Show")
                onTriggered: updateAction.trigger()
            }
        }
    }

    FeaturedModel {
        id: featuredModel
    }

    ListView {
        id: featureCategory
        model: featuredModel
        delegate: ColumnLayout {
            width: featureCategory.width
            Kirigami.Heading {
                Layout.fillWidth: true
                Layout.topMargin: Kirigami.Units.gridUnit
                Layout.leftMargin: Kirigami.Units.gridUnit
                text: categoryName
            }
            Kirigami.CardsListView {
                id: apps
                orientation: ListView.Horizontal 
                Layout.fillWidth: true
                Layout.preferredHeight: Kirigami.Units.gridUnit * 6
                Component.onCompleted: apps.leftMargin = Kirigami.Units.largeSpacing * 2
                snapMode: ListView.SnapToItem
                preferredHighlightBegin: Kirigami.Units.largeSpacing * 2
                preferredHighlightEnd: featureCategory.width - Kirigami.Units.largeSpacing * 2
                highlightRangeMode: ListView.ApplyRange
                keyNavigationWraps: true
                model: DelegateModel {
                    id: del
                    model: featuredModel
                    rootIndex: modelIndex(index)
                    delegate: MiniApplicationDelegate {
                        implicitHeight: Kirigami.Units.gridUnit * 5
                        implicitWidth: Kirigami.Units.gridUnit * 13
                        application: applicationObject
                    }
                }
                currentIndex: 0
            }
        }
    }
}
