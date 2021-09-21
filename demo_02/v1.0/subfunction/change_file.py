import os

def alter_file(old_cfg_name, new_cfg_name,n=1,**kargs):
    text_dic ={}
    if os.path.exists(new_cfg_name):#判断此文件是否存在 ，存在删除
        os.remove(new_cfg_name)
    with open(old_cfg_name, "r", encoding="utf-8") as f1:
        for line in f1:
            # print(line)
            text_dic[n]=line
            n+=1
        # print(n)
        # print(text_dic)
        #位置一定要对应准确，原来的cfg文件一定要固定不变
    if old_cfg_name == "yolov4-tiny.cfg" :
        text_dic[6] = "batch=" + kargs["batch"]
        text_dic[7] ="subdivisions=" + kargs["subdivisions"]
        text_dic[8] ="width="+ kargs["width"]
        text_dic[9] ="height=" +kargs["height"]
        text_dic[13] ="angle=" + kargs["angle"]
        text_dic[18] = "learning_rate="+kargs["learning_rate"]
        text_dic[20] ="max_batches="+ kargs["max_batches"]
        text_dic[22] = "steps="+kargs["steps"]
        text_dic[23] = "scales="+kargs["scales"]
        text_dic[212] = "filters="+kargs["filters"]
        text_dic[220] = "classes="+kargs["classes"]
        text_dic[263] = "filters="+kargs["filters"]
        text_dic[269] = "classes="+kargs["classes"]
        
    else:
        text_dic[2] ="batch=" + kargs["batch"]
        text_dic[3] = "subdivisions=" +kargs["subdivisions"]
        text_dic[5] = "width="+kargs["width"]
        text_dic[6] = "height=" +kargs["height"]
        text_dic[10] = "angle=" +kargs["angle"]
        text_dic[15] = "learning_rate="+kargs["learning_rate"]
        text_dic[17] = "max_batches="+kargs["max_batches"]
        text_dic[19] = "steps="+kargs["steps"]
        text_dic[20] ="scales="+ kargs["scales"]

        text_dic[959] = "filters="+kargs["filters"]
        text_dic[966] = "classes="+kargs["classes"]
        text_dic[1047] = "filters="+kargs["filters"]
        text_dic[1054] = "classes="+kargs["classes"]
        text_dic[1135] = "filters="+kargs["filters"]
        text_dic[1142] = "classes="+kargs["classes"]
    
    for cfg_vlaue in text_dic.values():
        # print(cfg_vlaue)
        with open(new_cfg_name, "a+", encoding="utf-8") as f2:
            f2.write(cfg_vlaue)



def read_class_file(file_path):
    '''
    读取类别文件，并且给出类别数量

    '''
    if os.path.exists(file_path):
        class_name=[]
        with open(file_path, 'r') as fp:
            lines = fp.readlines()
        for line in lines:
            print("line:",line)
            if line !=' 'and line !="\n":
                class_name.append(line)
        print("class_name:",class_name)
        return len(class_name)
def set_datafile(datafile_path):
    pass



