#-*- coding:utf-8 -*-
import re
import urllib.request
import time
xx=0

headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.116 Safari/537.36',
           	'Cookie':'BIDUPSID=8B0C9024D5F3240F76FEB48D37B30C34; PSTM=1594088171; BAIDUID=BDE3B19D2D75A646C719DFF301A5ED54:FG=1; BD_UPN=12314753; sug=3; sugstore=1; ORIGIN=0; bdime=0; COOKIE_SESSION=780_1_8_5_9_7_1_0_8_4_1_2_3346_0_300_511_1594853467_1594853678_1594853167%7C9%23391592_6_1594853167%7C3; delPer=0; BD_CK_SAM=1; PSINO=2; BDORZ=B490B5EBF6F3CD402E515D22BCDA1598; H_PS_PSSID=32219_1424_32141_32139_32046_32231_31709_26350_31639; H_PS_645EC=7841E0UXWIO0Nol1kmAnMWOPUIa9abGV0iIMlT7ixqBKoiyuucf6%2Be26Cx0'
	}

#path='https://www.baidu.com/s?&wd=%E4%BA%BA%E5%B7%A5%E6%99%BA%E8%83%BD&ie=utf-8'
path='https://www.baidu.com/s?rtt=1&bsst=1&cl=2&tn=news&word=%E4%BA%BA%E5%B7%A5%E6%99%BA%E8%83%BD'

with open('content1.txt','r',encoding='utf-8') as f:
  content1 = f.read()
with open('content2.txt','r',encoding='utf-8') as f:
  content2 = f.read()



starttime = time.time()
def fab():
    print('\r用时:', round(time.time() - starttime, 2),'     秒          ',end="")
    a=urllib.request.Request(url=path, headers=headers)
    b=urllib.request.urlopen(a).read().decode('utf-8')
    #zz=r'"sp_realtime_bigpic5"(.*?)"se_com_default"'
    zz=r'"content_left"(.*?)"gotoPage"'
    zzx=re.compile(zz,re.DOTALL)
    ulist=zzx.findall(b)
    #print(b)

    try:
        with open("index.html", "w", encoding='utf-8') as f:
            #f.write(ulist[0][200:-150])
            #f.write("<div id='content_left'"+ulist[0][:-10])
            f.write(content1+"<div id='content_left'"+ulist[0][:-10].replace(r'<em>人工智能</em>', '人工智能')+content2)
    except:
        fab()
    
fab()
print("ok")


