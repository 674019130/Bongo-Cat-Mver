   M S B A M L   `   `   `  ����I  EBongoCatMverUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null5clr-namespace:MyWpfApp.tutorialMyWpfApp.tutorial  5      *    $MyWpfApp.tutorial.Question_CatFreeze   5      \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      1localclr-namespace:MyWpfApp.tutorial     5        N� Title$  Question_CatFreeze��5	       � 	Resources 5       �� MergedDictionaries �� Source�� 5   
    5      �� 5      $ ../Bongocat_BtnStyle.xaml?�6%   %    5      .��5      � .+�5   
   �� $��80,0,0,0q�6   .+�5      �� $
��Left=�6   $��	10,10,0,0q�63   $
��Wrap=�6F   $9��3常见问题：猫咪的一部分或整体不动了��6Z   $��30(�6s   $	��Top=�6�   $��38��6�   �� 5      $��0,10,0,0q�6   |�.  ��.  $	��542��5   2      CatScrollViewer#��[  5      .��5      �� .+�5      �� $��
10,10,10,0q�6    $
��Wrap=�64   $��20(�6I   $	��Top=�6W   �� 5      $!�只有猫咪的鼠标不动��6   $
��Bold"�6'   5      �� 5       $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5!      $���        可能原因是游玩会锁定鼠标的游戏时没有开启“强制鼠标移动”。在“猫咪设置”将其打开即可。��6   5"      �� 5#      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5$      $���        在窗口捕获猫咪的情况下，猫咪被藏进屏幕边缘外的地方可能在直播软件中不会动，请将猫咪完整置于屏幕范围内。��6   5%      �� 5&      $��
10,10,10,0q�6    $
��Wrap=�64   $��20(�6I   $	��Top=�6W   �� 5'      $]�W猫咪不进行拍键盘的动作/不执行表情/不执行音频/不显示按键特效��6   $
��Bold"�6=   5(      �� 5)      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5*      $���        可能是错误设置了config.json，请自行检查是否有把键码写进另一个模式的错误，请自行检查相关键码是否还存在（群里有部分群友分享的素材包删除了某些键码）。��6   5+      �� 5,      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5-      $���        可能是文件缺失或替换了错误格式的文件或对文件进行了错误的命名。请检查自己文件的命名，请确保图片文件都是png格式、音频文件都是wav、flac、ogg格式。请确保没有将文件替换到错误的模式里（群里把standard模式素材替换进keyboard模式里去的不止一两个人）。��6   5.      �� 5/      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 50      $��}        可能是由于内存、硬盘等各种玄学原因导致读取文件失败，请尝试重启猫咪和重启电脑。��6   51      �� 52      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 53      $���        在窗口捕获猫咪的情况下，猫咪被藏进屏幕边缘外的地方可能在直播软件中不会动，请将猫咪完整置于屏幕范围内。��6   54      �� 55      $��
10,10,10,0q�6    $
��Wrap=�64   $��20(�6I   $	��Top=�6W   �� 56      $�猫咪整体都不动了��6   $
��Bold"�6&   57      �� 58      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 59      $P�J        可能是上述两种情况的混合，请先排除上述问题。��6   5:      �� 5;      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5<      $���        可能猫咪窗口因为某些原因被最小化了，任何被最小化的窗口在直播软件中都是不会动的。��6   5=      �� 5>      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5?      $���        在窗口捕获猫咪的情况下，猫咪被藏进屏幕边缘外的地方可能在直播软件中不会动，请将猫咪完整置于屏幕范围内。��6   5@      �� 5B      $��
10,10,10,0q�6    $
��Wrap=�64   $��14(�6I   $	��Top=�6W   �� 5C      $���        如果你直播或录屏的是全屏的osu!或全屏的Minecraft或其他导致猫咪不动的游戏。你需要在直播软件中以“游戏捕获”捕获猫咪，并为猫咪勾选“反作弊兼容”。��6   5D      5E      5G      5H      5I      5J      