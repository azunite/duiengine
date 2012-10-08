========================================================================
界面库：DUIEngine 项目概述
========================================================================

DUIEngine是一个开源的界面库，采用目前流行的DirectUI技术。该界面库从金山卫士
开源的界面部分(bkwin)演化而来，感谢金山卫士的无私贡献。

相比bkwin，DUIEngine经过全面重构，包括：
1、模块结构重新设计，采用公用的Singlton模板处理系统资源。
2、使用单层窗口设计。
3、放弃header,foot,body三部分界面模型。
4、设计一个CDuiFrame对象，用来处理DUI窗口嵌套，参考CDuiListBox。
5、重新设计图片管理模块，提供了CDuiBitmap及CDuiImgX两个对象，前者加载位图资源，
后者使用guiplus加载其它图片格式。
6、为窗口增加DuiGetDC,DuiReleaseDC接口。
7、模拟一套非客户区管理框架，实现ScrollView。
8、将对象包装到一个命名空间DuiEngine中。
9、将代码包装到一个单独的工程中，提供编译为静态库及动态库两种版本。
10、增加几个控件：CDuiRichedit,CDuiComboBox,CDuiSplitWnd,CDuiCaption,CDuiScrollBar等。
11、修改realwindow的管理模式。
12、实现控件的PretranslateMessage
13、实现一个自绘的菜单。
14、为窗口增加引用计数。
15、为窗口实现定时器。
16、使用32位位图作为缓冲区，支持将窗口配置为半透明模式。
17、其它