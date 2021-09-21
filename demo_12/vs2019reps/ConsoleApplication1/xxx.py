import win32api
import win32con
import win32gui
from ctypes import *
import time

import argparse
parser = argparse.ArgumentParser(description='manual to this script')
parser.add_argument('--midiKey', type=str, default = None)
#parser.add_argument('--batch-size', type=int, default=32)
args = parser.parse_args()
print(args.midiKey, type(args.midiKey))
#print(args.batch_size, type(args.batch_size))

def mouse_click(x=338,y=779, TM=0.1,test=None):
    print(x,y,TM,test)
    if test==None:
        x=338+13*x
        y=799
    win32api.SetCursorPos((x,y))
    time.sleep(TM)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)

if args.midiKey!=None:
    TheKey=args.midiKey
    quick=0.000000001
    if TheKey=='C' or TheKey=='1':
        mouse_click(+0,+0,quick)
    if TheKey=='D' or TheKey=='2':
        mouse_click(+1,+1,quick)
    if TheKey=='E' or TheKey=='3':
        mouse_click(+2,+2,quick)
    if TheKey=='F' or TheKey=='4':
        mouse_click(+3,+3,quick)
    if TheKey=='G' or TheKey=='5':
        mouse_click(+4,+4,quick)
    if TheKey=='A' or TheKey=='6':
        mouse_click(+5,+5,quick)
    if TheKey=='B' or TheKey=='7':
        mouse_click(+6,+6,quick)
    if TheKey=='c' or TheKey=='8':
        mouse_click(+7,+7,quick)
    if TheKey=='d' or TheKey=='9':
        mouse_click(+8,+8,quick)
    if TheKey=='e' or TheKey=='0':
        mouse_click(+9,+9,quick)
else:
    print("nook")

"""
if __name__ == "__main__":    # whith test
    pos = win32api.GetCursorPos()
    print("this point->",int(pos[0]), int(pos[1]))
    win32api.SetCursorPos((200, 200))
    hw = win32gui.WindowFromPoint(win32api.GetCursorPos())
    print("window->",hw)
    print("windowCl->",win32gui.GetClassName(hw))
    print("windowNM->",win32gui.GetWindowText(hw))
    for i in range(29):#c→+13
        mouse_click(338+i*13,799,0.1,1)
    for i in range(24):#c←-13
        mouse_click(338-i*13,799,0.1,1)
"""