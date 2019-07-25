# BimHousePlayer

#### 介绍

UE4动态加载模型支持FBX/OBJ等等，使用assimp库。UI使用蓝图开发，功能使用C++开发
目前实现功能： 
1. 动态加载模型
2. 射线选取，高亮
3. 碰撞检测
4. 动态生成菜单
5. 自定义插件
6. 右键弹出菜单

#### 效果图
- 打开本地文件
![输入图片说明](https://files.gitee.com/group1/M00/08/B5/PaAvDF0240GAS30FAAnOp_BR1rg116.png?token=ef544bae61dd306a6f52320fe7828438&ts=1563878482&attname=%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20190723183650.png&disposition=attachment "打开本地文件")
- 高亮，射线选取
![输入图片说明](https://files.gitee.com/group1/M00/08/B5/PaAvDF0242GAKfC0ABEK46ZJrBw859.png?token=7f97c7b25fff3c4f10f0c2200576ebdf&ts=1563878551&attname=%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20190723183542.png&disposition=attachment "高亮，射线选取")
- 碰撞检测
![输入图片说明](https://files.gitee.com/group1/M00/08/B5/PaAvDF0243mAG9POACMWQuyCE4Y531.png?token=3c66c14750ba010e10e2236c10bfe662&ts=1563878564&attname=%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20190723183702.png&disposition=attachment "碰撞检测")
- 右键弹出菜单
![输入图片说明](https://files.gitee.com/group1/M00/08/B5/PaAvDF025bCAX6ykAAvEt6_Aep0343.png?token=f1357abd8baf494b24a0ada49e07860e&ts=1563878840&attname=%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_222234.png&disposition=attachment "右键弹出菜单")

#### 使用说明


1. 使用UE4.20以上版本加载工程文件
2. 如果第一步build失败，请将..\ThirdParty\assimp\bin\x64目录下的assimp-vc140-mt.dll拷贝到..\Binaries\Win64目录下即可
3. 打开.bhp文件，bhp是自定义的文件格式，里面定义了场景的相关描述信息，json格式，导入的模型需要放在..\Scenes目录下

#### .bhp文件说明

```
{
    "SystemInfo":{
        "version":"1.0",
        "leftHand":true,
        "up":"z",
        "unit":"cm"
    },
    "Home":[
        {
            "style":"空载",
            "room":[
                {
                    "roomID":"KT",
                    "additions":[
                        
                    ]
                }
            ],
            "Mesh":[
                {
                    "guid":"canzhuo",
                    "suffix":"obj",
                    "name":"123",
                    "currentMaterial":"bh2321231hh112",
                    "materialList":[
                        "31231231",
                        "12312312",
                        "23232323"
                    ],
                    "meshList":[
                        "1231232",
                        "1232132"
                    ],
                   
                    "rotation":[
                        0,
                        0,
                        0
                    ],
                    "scale":[
                        0,
                        0,
                        0
                    ]
                }
            ],
            "Material":[
                "1231221434",
                "1234122222"
            ],
            "Light":[
                {
                    "guid":"123123123",
                    "name":"sdasdasda",
                    "type":"point",
                    "position":[
                        0,
                        0,
                        0
                    ],
                    "rotation":[
                        0,
                        0,
                        0
                    ],
                    "scale":[
                        1,
                        1,
                        1
                    ],
                    "target":[
                        0,
                        0,
                        0
                    ],
                    "angle":45,
                    "length":0,
                    "width":0,
                    "color":[
                        255,
                        255,
                        255
                    ],
                    "strength":10
                }
            ]
        },
        {
            "style":"深色",
            "room":[
                {
                    "roomID":"KT",
                    "additions":[
                        "1231231",
                        "123234",
                        "656565"
                    ]
                }
            ],
            "Mesh":[
                {
                    "guid":"2312312nh123j1h3",
                    "name":"zuiaahhh",
                    "currentMaterial":"bh2321231hh112",
                    "MaterialList":[
                        "31231231",
                        "12312312",
                        "23232323"
                    ],
                    "meshList":[
                        "1231232",
                        "1232132"
                    ],
                    "roomID":"KT",
                    "saleType":1,
                    "meshType":"door",
                    "position":[
                        0,
                        0,
                        0
                    ],
                    "rotation":[
                        0,
                        0,
                        0
                    ],
                    "scaler":[
                        0,
                        0,
                        0
                    ]
                }
            ],
            "Material":[
                {
                    "guid":"1231221434",
                    "name":"木饰面",
                    "type":1,
                    "baseColor":[
                        0,
                        0,
                        0,
                        1
                    ],
                    "diffuseMap":"./Texture/木纹.jpg",
                    "UVOffsetX":0,
                    "UVOffsetY":0,
                    "UVScaleX":0.1,
                    "UVScaleY":0.25,
                    "metallic":0.1,
                    "roughness":0.7,
                    "specular":0.4,
                    "emissive":false,
                    "opacity":1
                }
            ],
            "Light":[
                {
                    "guid":"123123123",
                    "name":"sdasdasda",
                    "type":"point",
                    "position":[
                        0,
                        0,
                        0
                    ],
                    "rotation":[
                        0,
                        0,
                        0
                    ],
                    "scale":[
                        1,
                        1,
                        1
                    ],
                    "target":[
                        0,
                        0,
                        0
                    ],
                    "angle":45,
                    "length":0,
                    "width":0,
                    "color":[
                        255,
                        255,
                        255
                    ],
                    "strength":10
                }
            ]
        }
    ]
}
```

#### 后续计划
空闲时会不定期添加功能，主要看时间或者大家有什么希望添加的功能也可以提出来


