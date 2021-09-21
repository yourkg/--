# coding: utf-8
# 主管通讯，即url调度
from flask import Flask
from flask import render_template, request, jsonify
import json
import os
import _thread
import time

from user import User #user.py的内容

from gevent.pywsgi import WSGIServer
from geventwebsocket.handler import WebSocketHandler

###########################################
#copy于v0.3修改2版的main.py的前30行不重复内容
from subfunction.change_file import alter_file, read_class_file
from subfunction.set_ratio import training_set, writer_objfile

if os.path.exists("user.log"):#判断此文件是否存在 ，存在删除
    os.remove("user.log")
fp = open("user.log","w")
fp.close()
###########################################


PATH="C:/Users/mail/Desktop/Xflask_demo/v1.0/test/" 




app = Flask(__name__)
app.config['JSON_AS_ASCII'] = False

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

@app.route('/')
def index(): 
    '''
    可以理解为登录。
    '''
    loginuser=User('test_user')
    return render_template('index.html',login_user="test_user",user_room=round(loginuser.haveGb(),3))

def readLastLine(filepath): #已更新为0.3修改2版代码
    with open(filepath, 'r') as fp:
         lines = fp.readlines()
    if lines:     
        last_line = lines[-1]
    else:
        last_line ='\n'
    return last_line

@app.route('/via',methods=['GET', 'POST'])#0.5新增内容
def go2via():
    if request.method == "GET":
        print(request.args.get("userId"),request.args.get("trainSetId"))
        return render_template('via.html',login_user="test_user",train_set=request.args.get("trainSetId"))
    if request.method == "POST":
        thisUser=User(request.form.get('userid'))
        return jsonify({'code':200,'status':1,'IMAGES':thisUser.getTrainSet(request.form.get('trainid'))})

ISRUN=False 

def to_thread(cmd):
    global ISRUN
    ok=os.system(PATH+cmd+" >> user.log ")
    #print(PATH+cmd+" >> user.log ")
    ISRUN=False
    return

@app.route('/logicMe/',methods = ["GET","POST"])#测试需要，没有加入0.3修改版内容
def logic(): 
    global ISRUN 
    if request.method == "POST":
        cmd = request.form.get('cmd')#type=str, default=None)
        #ip = request.remote_addr
        if cmd :
            if ISRUN: 
                last_line=readLastLine('user.log')
                time.sleep(0.5) #由后端控制轮询速度
                return jsonify({'code':200,'status':1,'msg':last_line})
            elif int(request.form.get('isFirst'))==1: 
                ISRUN=True 
                _thread.start_new_thread(to_thread, ('print',)) 
                last_line="0.5版该语句无效\n"
                return jsonify({'code':200,'status':1,'msg':last_line}) 
            else:
                last_line=readLastLine('user.log') 
                return jsonify({'code':200,'status':1,'msg':last_line,'end':1}) 

            ##json.dumps(dic,ensure_ascii=False) #个人笔记：这种方式需要前端使用JSON.parse，django常用这种
            ##return jsonify({'code':200,'status':1,'msg':last_line})
        else:
            return jsonify({'code':400,'message':'Error'})

@app.route('/addObject/',methods = ["GET","POST"])#0.5版新增内容
def addObject(): #且包含增加训练集的交互
    if request.method == "POST":
        thisUser=User(request.form.get('userid'))
        if request.form.get('what')=='object':
            if thisUser.add_obj(request.form):
                return jsonify({'code':200,'status':1,'msg':"okk"}) 
        elif request.form.get('what')=='trains':
            #if thisUser.add_obj(request.form):
            upload_files=request.files.getlist('FILE')
            #print("------>",upload_files)
            if thisUser.add_trainImg(request.form,upload_files):
                print(request.form)
                return jsonify({'code':200,'status':1,'msg':"okk"}) 

@app.route('/TrainSetLabelsAdd/',methods = ["GET","POST"])#0.5版新增内容
def userTrainSetLabel():
    if request.method == "POST":
        thisUser=User(request.form.get('userid'))
        if thisUser.leabels('add',request.form.get('trainid'),json.loads(request.form.get('labels'))):
            return jsonify({'code':200,'status':1,'msg':"okk"})
        
@app.route('/loadUser/',methods = ["GET","POST"])#0.5版新增内容
def loadUser():
    #读出用户的文件菜单
    if request.method == "POST":
        thisUser=User(request.form.get('userid'))
        reqList=thisUser.getUserlis(request.form.get('what'))
        return jsonify({'code':200,'status':1,'msg':reqList,'serverFiles':len(os.listdir('./static/public_train/images/'))}) 

@app.route('/deletit/',methods = ["GET","POST"])
def deletit():
    if request.method == "POST":
        thisUser=User(request.form.get('userid'))
        if request.form.get('what')=='trains':
            if thisUser.delet_trains(request.form.get('thisis')):
                return jsonify({'code':200,'status':1,'msg':"okk"})


@app.route('/ws')#websocket试验，参考https://www.cnblogs.com/yb635238477/p/9795097.html
def ws():
    print(request.environ.get('wsgi.websocket'))
    print(request.environ)
    user_socket = request.environ.get('wsgi.websocket') # type: WebSocket
    if user_socket:    
        while 1:
            msg = user_socket.receive() # 接受消息
            print(msg)
            user_socket.send(msg)  # 发送消息


@app.route('/go03')#进入0.3修改版
def index03():
    return render_template('index03.html')
@app.route('/logicMake/',methods = ["GET","POST"])#0.3修改版内容完全copy,由于路径问题无法测试
def logicMake(): 
    if request.method == "POST":
        print("用户创建"+request.form.get('mdList1')+" +cfg:"+request.form.get('mdList2'))
        print(request.form.get('class_names'))
        names = request.form.get('class_names')
        class_names_path=r"D:\test_yolov4\classes.names"
        if os.path.exists(class_names_path):#判断此文件是否存在 ，存在删除
            os.remove(class_names_path) 
        with open(class_names_path, "a+", encoding="utf-8") as f2:
            f2.write(names)
        
        class_num = read_class_file(class_names_path)
        print("class_num:",class_num)
        print(type(class_num))
        percent = request.form.get('ratio')
        print("---",percent)
        #  class_names_path train_path  val_path obj.data 放在先前设置的文件夹中 同一个文件夹中 文件夹必须用英文命名
        # weight_save 设置存放的文件夹
        class_names_path=r"D:\test_yolov4\classes.names" #放着类别名称的文件
        weight_save=r"D:\test_yolov4\yolov4_train" #选择存放训练完成后权重的文件夹
        train_path = r"D:\test_yolov4\train.txt" #放着训练的图片路径的txt文件
        val_path = r"D:\test_yolov4\val.txt" # #放着验证的图片路径的txt文件
        obj_data_path = r"D:\test_yolov4\obj.data" #放训练综合文件的文件
        #前端选择标注完成训练的文件夹
        train_floder = [r"E:\yolov3_train2_pig20201216\images"]#数据集文件夹列表 选择
        
        if percent =="0":            
            training_set(percent,train_floder,train_path)
            writer_objfile(percent,class_num,class_names_path,train_path,weight_save,obj_data_path)
        print("^^^",val_path)
        training_set(percent,train_floder,train_path,val_path=val_path)
        
        writer_objfile(percent,class_num,class_names_path,train_path,weight_save,obj_data_path,val_path=val_path)
        #此处添加的YOLO调整参数，其他模型需要跳转
        if request.form.get('mdList1') == "yolov4":
            cfg_parame = {} 
            cfg_parame["batch"] = request.form.get('batch')+"\n"
            # print("batch",request.form.get('batch'))
            cfg_parame["subdivisions"] = request.form.get('subdivisions')+"\n"
            cfg_parame["width"] = request.form.get('width')+"\n"
            cfg_parame["height"] = request.form.get('height')+"\n"
            # print("angle",request.form.get('angle'))
            cfg_parame["angle"] = request.form.get('angle')+"\n"

            cfg_parame["learning_rate"] = request.form.get('learning_rate')+"\n"
            cfg_parame["max_batches"] = request.form.get('max_batches')+"\n"
            cfg_parame["steps"] = request.form.get('steps')+"\n"
            cfg_parame["scales"] = request.form.get('scales')+"\n"

            cfg_parame["classes"] = str(class_num)+"\n" #得到类别的数量
            cfg_parame["filters"] = str((int(class_num)+5)*3)+"\n" #计算最后一层filters数量 (类别数+5)*3
            print(cfg_parame["filters"])
            

            if request.form.get('mdList2') =="yolov4-tiny.cfg":
                old_cfg_name = "yolov4-tiny.cfg" #存放tiny.cfg原地址
                new_cfg_name = os.path.join(r"D:\test_yolov4",time.strftime("%d_%m_%Y_")+"user_yolov4-tiny.cfg")#新地址新名字
                alter_file(old_cfg_name,new_cfg_name,**cfg_parame) #调用生成文件函数

            elif request.form.get('mdList2') =="yolov4.cfg":
                old_cfg_name = "yolov4.cfg" #存放cfg原地址
                new_cfg_name = os.path.join(r"D:\test_yolov4",time.strftime("%d_%m_%Y_")+"user_yolov4-tiny.cfg") #新地址新名字      
        #......
        return jsonify({'code':200,'status':1,'msg':"okk"}) 

if __name__ == '__main__':
    #app.run(host='0.0.0.0', port=8910, debug=True)
    http_serv = WSGIServer(('0.0.0.0',8910),app,handler_class=WebSocketHandler)
    http_serv.serve_forever()
