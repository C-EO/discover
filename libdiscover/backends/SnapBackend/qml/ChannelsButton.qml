/*
 *   SPDX-FileCopyrightText: 2018 Aleix Pol Gonzalez <aleixpol@blue-systems.com>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kirigami.delegates as KD
import org.kde.discover as Discover

QQC2.Button {
    id: root

    text: i18nd("libdiscover", "Channels…")

    onClicked: overlay.open()
    visible: resource.isInstalled /*&& view.count > 0*/

    Kirigami.OverlaySheet {
        id: overlay

        parent: root.QQC2.Overlay.overlay
        title: i18nd("libdiscover", "%1 channels", resource.name)

        ListView {
            id: view

            model: resource.channels(root).channels
            delegate: QQC2.ItemDelegate {
                id: delegate

                required property var modelData

                readonly property bool current: resource.channel === modelData.name

                text: i18nd("libdiscover", "%1 - %2", modelData.name, modelData.version)

                contentItem: RowLayout {
                    spacing: Kirigami.Units.smallSpacing
                    KD.IconTitleSubtitle {
                        Layout.fillWidth: true
                        icon: icon.fromControlsIcon(delegate.icon)
                        title: delegate.text
                        selected: delegate.highlighted
                        font: delegate.font
                    }

                    QQC2.Button {
                        text: i18nd("libdiscover", "Switch")
                        enabled: !delegate.current
                        onClicked: resource.channel = delegate.modelData.name
                    }
                }
            }
        }
    }
}
