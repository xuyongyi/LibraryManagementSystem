# LibraryManagementSystem
基于Qt的图书管理系统的设计与实现

软件搭建环境：Windows10、Visual Studio2019、MySQL数据库v5.7、Navicat、Qt5

项目描述：本系统是根据读者、图书管理员、系统管理员三个端的用户的不同需求来进行设计的。

前端功能：读者的登录、注销、信息修改，书籍信息浏览，书籍的借阅、预约、归还、续借，图书的分类与检索，图书借阅排行，借阅、预约历史查看等功能。
后端功能：管理员登录、管理员与读者的信息修改，新书上架、旧书下架、查询借阅历史，到期提醒和系统相关信息的修改等。


技术实现：1.采用 Qt 作为项目与的界面设计和系统功能设计。
         2.使用 QSS 语言和 Element UI 进行 UI 的设计与美化。
         3.使用 Navicat 进行 MySQL 数据库的管理，MySQL 数据库中存储了图书、读者、管理员、图书借阅和预约等信息。
项目职责：本人负责整个系统的需求分析，前台的界面设计、后台的功能设计，系统功能的维护等。

注意：本程序是本人的毕业设计，主要是用于展示，所以是搭建的本地的MySQL数据库，并没有搭建到云服务器上。
所以如果要正常的运行的话，需要先自行在自己的电脑上搭建MySQL v5.7数据库的本地环境并且安装相关软件，然后在该服务器下创建一个名称为“book”的数据库，
然后导入相关的图书信息。

编译环境：

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/9644de56-c40f-4584-99e8-dffc1949051b)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/5775f1cf-45f5-468a-b63b-368ccd2f38b4)

源代码文件分类窗口如下：

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/674cec00-f6bb-411a-98af-f038c3513a7e)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/f09db59d-b693-4721-9ad0-4c52dbf04c95)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/3407dcf1-5262-415a-8dec-0fa506413293)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/ca988bbb-889c-4384-897f-8405f3c10656)


系统的实现思路：

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/0d04fed8-c7ed-4949-a225-8c093f1914dd)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/c3dcd6cc-cded-46bc-8c8c-b84078354012)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/b4583f5c-e213-4984-b392-bc376f2e9679)
![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/7c36ae15-4f79-4055-bbf0-b42f50979d4c)


软件的部分前台界面展示:

①图书管理系统主界面：

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/c92c0d9c-48cc-476a-a439-29d3619fe4d7)

②登录界面：

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/3ccf90a7-ef8e-4b07-bc88-0718b63a9bca)

③注册界面

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/75d43b88-41dd-4704-bea6-7bb722030d74)

④个人信息修改界面

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/3bf3cca2-56c5-40f0-9912-366e30da1ced)

软件的部分后台界面展示:

① 学生/老师身份

1.图书信息检索

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/3b527255-4c75-4d2e-b224-cfe7b42b95f6)

2.还书和续借图书

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/440e5c73-b7d6-4f3e-a1b1-e4a37a85dce0)

3.图书预约信息

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/9617c681-87df-4fc6-ae85-250e7717e14f)

4.图书借阅排行榜

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/61c5af8c-344d-42c6-8c0c-4ac145339d9d)

5.个人中心

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/ffa137ec-8e68-407c-9ea1-37cb97fd466c)

②图书管理员身份

1.图书相关信息管理

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/e68d0e5c-2d5e-46ca-becb-b7734b692149)

2.读者相关信息管理

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/b7c01bdd-872f-42be-917f-44bd2a9dacc5)

3.辅助读者进行图书借阅和预约

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/c08523be-1e72-4801-a384-491929eeffb9)

4.辅助读者进行图书续借和归还

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/79398616-8fad-40c7-890b-3ac435be284f)

5.个人中心

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/22ce5363-5666-4617-8214-1349281e6688)

③系统管理员身份

1.图书管理员信息管理

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/eb07a31e-4d50-4322-811f-89b96bcd1ac9)

2.图书允许最长的预约时长设置

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/deb9bb31-fbac-4020-b7bc-bddd49100542)

3.图书单次借阅的时长设置

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/dbe5ad30-f1f6-474a-a280-0d1f885da5bc)

4.图书超期归还后，缴纳的滞纳金的设置

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/bbd3866d-454a-4abc-a41c-00c4e909673c)

5.系统维护的时长设置

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/8d6e1e58-3513-40bf-892a-b97b209b11e3)

6.个人中心界面

![image](https://github.com/loney123456/LibraryManagementSystem/assets/35869270/21704505-fc25-404a-a58e-85ab758f6d2e)

