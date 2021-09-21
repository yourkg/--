#用户相关的都在这，
# coding: utf-8

import os
import random
import json

def getFileSize(filePath, size=0):
    for root, dirs, files in os.walk(filePath):
        for f in files:
            size += os.path.getsize(os.path.join(root, f))
    return size

def del_dir_tree(path):
    if os.path.isfile(path):
        try:
            os.remove(path)
        except:
            print("error02")
    elif os.path.isdir(path):
        for item in os.listdir(path):
            itempath = os.path.join(path, item)
            del_dir_tree(itempath)
        try:
            os.rmdir(path)
        except:
            print("error01")
    return True

class User:
    """
    用户类，用于囊括用户相关的操作，。。
    """
    def __init__(self, uid):
        if not os.path.exists('./users/'+uid):
            os.makedirs('./users/'+uid+'/myobject/')
            os.mkdir('./users/'+uid+'/mytrains/')
        self.urlobj='./users/'+uid+'/myobject/'
        self.urltra='./users/'+uid+'/mytrains/'
        self.name = uid
        self.room = getFileSize('./users/'+uid)/1024/1024/1024

    def haveGb(self):
        return self.room

    def add_obj(self,somewhat):
        #print("----->",somewhat)
        os.mkdir(self.urlobj+somewhat.get('objname')+'/')
        inUrlobj=self.urlobj+somewhat.get('objname')
        str="batch="+somewhat.get('batch')+"\nsubdivisions="+somewhat.get('subdivisions')+"\nwidth="+somewhat.get('width')+"\nheight="+somewhat.get('height')+"\nchannels=3\nmomentum=0.9\ndecay=0.0005\nangle=0\nsaturation = 1.5\nexposure = 1.5\nhue=.1\nlearning_rate=0.00261\nburn_in=1000\nmax_batches = "+somewhat.get('max_batches')+"\npolicy=steps\nsteps="+somewhat.get('steps')+"\nscales="+somewhat.get('scales')
        with open('yolov4-tiny.a', 'r') as fp:
              page1 = fp.read()
        with open('yolov4-tiny.z', 'r') as fp:
              page2 = fp.read()
        f = open(os.path.join(inUrlobj+'/user_yolov4-tiny.cfg'), 'w')
        f.write(page1+str+page2)
        f.close()
        f = open(os.path.join(inUrlobj+'/describe.txt'), 'w')
        f.write(somewhat.get('objtxt'))
        f.close()
        #新增
        imList=self.getTrainSet(somewhat.get('使用的训练集名'))
        random.shuffle(imList)
        bl=somewhat.get('训练图像比例')
        if bl=='1':
            gs=1.0*len(imList)
        elif bl=='2':
            gs=0.8*len(imList)
        elif bl=='3':
            gs=0.9*len(imList)
        else:
            gs=int(bl.split('.')[0])
        #print("----->",int(gs))
        txttrain=''
        txtval=''
        k=0
        for i in imList:
            if k<int(gs):
                txttrain+=i['url']+'\n'
            else:
                txtval+=i['url']+'\n'
            k+=1
        f = open(os.path.join(inUrlobj+'/train.txt'), 'w')
        f.write(txttrain)
        f.close()
        f = open(os.path.join(inUrlobj+'/val.txt'), 'w')
        f.write(txtval)
        f.close()
        #以下内容仅意思意思
        txtdata="classes=?\n"
        txtdata+=inUrlobj+'/train.txt\n'
        txtdata+=inUrlobj+'/val.txt\n'
        txtdata+="???????class_name\n"
        txtdata+="???????\n"
        f = open(os.path.join(inUrlobj+'/xxx.data'), 'w')
        f.write(txtdata)
        f.close()
        return True
    def delet_trains(self,who):
        if del_dir_tree(self.urltra+who):
            return True
    def add_trainImg(self,somewhat,someImages):
        print("----->",somewhat.get('trainSetName'))
        os.mkdir(self.urltra+somewhat.get('trainSetName')+'/')
        inUrltra=self.urltra+somewhat.get('trainSetName')
        f = open(os.path.join(inUrltra+'/describe.txt'), 'w')
        f.write(somewhat.get('howManyImg'))
        f.close()
        if somewhat.get('constImg')!=0:
            print("需要读"+somewhat.get('constImg')+"个路径")
            k=int(somewhat.get('constImg'))-1
            kstr=''
            for file in os.listdir('./static/public_train/images/'):
                file_path = os.path.join('./static/public_train/images/', file)
                kstr+=file_path+'\n'
                if k==0:
                    break
                k-=1
            with open(inUrltra+'/imglist.txt', mode='a') as filename:
                filename.write(kstr)
        if somewhat.get('upImg')=='UPIMG':
            os.mkdir(inUrltra+'/uploadimg/')#实际没放东西
            try:
                os.mkdir('./static/user_img/'+self.name+'/')#实际放在了这
            except:
                pass
            kstr=''
            for upload in someImages:
                filename = upload.filename.rsplit("/")[0]
                #print(filename)
                #upload.save(inUrltra+'/uploadimg/'+filename)#后期改进用这
                upload.save('./static/user_img/'+self.name+'/'+filename)
                kstr+='./static/user_img/'+self.name+'/'+filename+'\n'
            with open(inUrltra+'/imglist.txt', mode='a') as filename:
                filename.write(kstr)
        return True
    def getUserlis(self,how):
        Lists=[]
        objects=[]
        if how == 'object':
            for root, dirs, files in os.walk(self.urlobj):
                if dirs!=[]:
                    objects=dirs
                    break
            for i in objects:
                objsw={'name':i,'describe':''}
                with open(self.urlobj+i+'/describe.txt', 'r') as fp:
              	    objsw['describe'] = fp.read()
                Lists.append(objsw)
        elif how == 'trains':
            for root, dirs, files in os.walk(self.urltra):
                if dirs!=[]:
                    objects=dirs
                    break
            for i in objects:
                objsw={'name':i,'describe':''}
                with open(self.urltra+i+'/describe.txt', 'r') as fp:
              	    objsw['describe'] = fp.read()
                Lists.append(objsw)
        return Lists
    def getTrainSet(self,Name):
        TRA={'Lists':[],'Labels':''}
        #print("---->",Name)
        for line in open(self.urltra+Name+"/imglist.txt"):
            kdict={}
            (path, filename) = os.path.split(line[:-1])
            kdict['name']=filename
            kdict['size']=10
            kdict['url']=line[:-1]
            TRA['Lists'].append(kdict)
        #print(Lists)
        try:
            with open(self.urltra+Name+'/labels.json', 'r') as fp:
                TRA['Labels'] = fp.read()
        except:
            pass
        return TRA
    def leabels(self,whatdo,who,value):
        if whatdo=='add':
            try:
                os.mkdir(self.urltra+who+'/labels/')
            except:
                pass
            js = json.dumps(value)
            file = open(self.urltra+who+'/labels.json', 'w')
            file.write(js)
            file.close()
            ll=0
            lk=[]
            for i in value:
                imgName=value[i]['filename'].split('.')[0]
                for j in value[i]['regions']:
                    className=''
                    for k,v in value[i]['regions'][j]['region_attributes'].items():
                        className=v
                        break
                    if className in lk:
                        ll=lk.index(className)
                    else:
                        lk.append(className)
                        ll=lk.index(className)
                    #这里有一个优化方向是使用w+模式写，需要调整代码上下文，0.7版更新(误),项目已经完了。。
                    #print(str(ll)+" "+str(value[i]['regions'][j]['shape_attributes']['x'])+" "+str(value[i]['regions'][j]['shape_attributes']['y'])+" "+str(value[i]['regions'][j]['shape_attributes']['width'])+" "+str(value[i]['regions'][j]['shape_attributes']['height'])+"\n")
                    with open(self.urltra+who+'/labels/'+imgName+'.txt',"a") as file:
                        file.write(str(ll)+" "+str(value[i]['regions'][j]['shape_attributes']['x'])+" "+str(value[i]['regions'][j]['shape_attributes']['y'])+" "+str(value[i]['regions'][j]['shape_attributes']['width'])+" "+str(value[i]['regions'][j]['shape_attributes']['height'])+"\n")
            lkstr=''
            for i in lk:
                lkstr+=i+'\n'
            with open(self.urltra+who+'/xxx.names',"w") as file:
                        file.write(lkstr)
            return True
    def __str__(self):
        return "我是用户类！"
