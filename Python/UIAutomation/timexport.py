import uiautomation as auto
import win32api as win
from win32con import *
from time import sleep, strftime
from datetime import datetime

# tested on TIM 3.4.1(22056)


def goToParent(control, n: int):
    for _ in range(n):
        control = control.GetParentControl()
    return control


def getToolTipText(window):
    return window.ToolTipControl(searchDepth=1).Name


class TIMCloudTable:
    def __init__(self, windowControl):
        self.windowControl = windowControl

        # get file list
        anchor = self.windowControl.TextControl(searchDepth=20, Name="更新时间")
        anchor = goToParent(anchor, 4)
        self.listControl = anchor.ListControl(searchDepth=1)

        # resize the window
        margin = (
            self.windowControl.BoundingRectangle.height()
            - self.listControl.BoundingRectangle.height()
        )
        self.windowControl.GetTransformPattern().Resize(
            self.windowControl.BoundingRectangle.width(), margin + 40 * 20
        )

    def switchToWindow(self):
        self.windowControl.SwitchToThisWindow()

    def scroll(self, offset: int = WHEEL_DELTA):
        oldPos = win.GetCursorPos()
        geometry = self.listControl.BoundingRectangle
        newPos = (geometry.xcenter(), geometry.ycenter())

        self.switchToWindow()
        win.SetCursorPos(newPos)
        sleep(0.1)
        # win.mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
        # win.mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)
        win.mouse_event(
            MOUSEEVENTF_WHEEL,
            0,
            0,
            offset,
            0,
        )
        win.SetCursorPos(oldPos)

    def scrollUp(self):
        self.scroll(WHEEL_DELTA)

    def scrollDown(self):
        self.scroll(-WHEEL_DELTA)

    def getItemCount(self):
        return len(self.listControl.PaneControl(searchDepth=1).GetChildren())

    def getItemList(self, id: int = 0):
        # foundIndex starts from 1
        # id starts from 0
        # use the top position to sort
        result = []
        anchor = self.listControl.PaneControl(searchDepth=1)
        for listItem in anchor.GetChildren():
            result.append(
                (
                    listItem.BoundingRectangle.top,
                    listItem.PaneControl(searchDepth=1, foundIndex=2)
                    .PaneControl(searchDepth=1)
                    .PaneControl(searchDepth=1),
                ),
            )
        result.sort(key=lambda x: x[0])
        return [unit[1] for unit in result]

    def getItemFilename(self, item):
        return (
            item.PaneControl(searchDepth=1, foundIndex=1)
            .GetLegacyIAccessiblePattern()
            .Description
        )

    def getItemUpdateTime(self, item):
        anchor = item.PaneControl(searchDepth=1, foundIndex=2)
        result = anchor.GetLegacyIAccessiblePattern().Description
        if len(result) == 0:  # 下载失败？
            result = anchor.TextControl(searchDepth=1).Name
        return result

    def getItemSource(self, item):
        result = ""
        try:
            result = (
                item.PaneControl(searchDepth=1, foundIndex=3)
                .GetLegacyIAccessiblePattern()
                .Description
            )
        except Exception as e:
            result = ""  # 下载失败
        return result

    def getItemSize(self, item):
        result = ""
        try:
            result = (
                item.PaneControl(searchDepth=1, foundIndex=4)
                .GetLegacyIAccessiblePattern()
                .Description
            )
        except Exception as e:
            result = ""  # 下载失败
        return result


if __name__ == "__main__":
    auto.uiautomation.SetGlobalSearchTimeout(5)

    print(datetime.now(), "start")
    timWindow = auto.WindowControl(searchDepth=1, ClassName="TXGuiFoundation")
    table = TIMCloudTable(timWindow)

    table.switchToWindow()

    with open(
        "data-" + datetime.now().strftime("%Y-%m-%d-%H-%M-%S") + ".txt",
        "w",
        encoding="utf-8",
    ) as f:

        last = ""
        cnt = 0
        for i in range(400):
            print(datetime.now(), "page:", i + 1)
            all = ""
            for item in table.getItemList():
                try:
                    data = table.getItemFilename(item)
                    data += "###"
                    updateTime = table.getItemUpdateTime(item)
                    data += updateTime
                    if updateTime != "下载失败":
                        data += table.getItemSource(item) + table.getItemSize(item)
                except Exception as e:
                    print("error: unexpected item")
                    print(repr(e))
                    table.scroll(10)
                    continue
                # print(data)
                all += data + "\n"

            table.scroll(-13 * 40)
            sleep(2)

            if cnt >= 3:
                break
            if all == last:
                print("error:same data")
                cnt += 1
            else:
                f.write(all + "\n")
                cnt = 0
            last = all

    print(datetime.now(), "finished")
