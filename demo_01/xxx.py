#dec12 version 0.1

import itchat
import openpyxl

itchat.auto_login()

friendlist=itchat.get_friends()

wb = openpyxl.Workbook()
ws=wb.create_sheet(index=0,title='Friend List')

ws.append(list(friendlist[0].keys())[1:])

for x in friendlist:
   oldList=list(x.values())[1:]
   newList=[]
   newList.append(oldList[1])
   newList.append(oldList[7])
   newList.append(oldList[12])
   ws.append(newList)

wb.save(filename='test.xlsx')


