"""
描    述：Gemini交互界面

当前版本：v1.0
作   者：YRQ
完成日期：2024/6/27

此代码使用 PyQt5 和 PyQt-Fluent-Widgets 库创建了一个用于测试的 GUI 应用程序，用户可以选择模型并输入提示语进行提交，结果显示在界面上。
"""
# ---------------------------------------------------------------------------------------------------------------------
# 导入所需的库和模块
from PyQt5.QtWidgets import QMainWindow, QVBoxLayout, QWidget, QLabel, QStackedWidget
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtCore import Qt
from qfluentwidgets import setTheme, Theme, LineEdit, PrimaryPushButton, ComboBox, TextEdit, InfoBar, InfoBarPosition, Pivot
# ---------------------------------------------------------------------------------------------------------------------

class GeminiApp(QMainWindow):
    def __init__(self, on_submit_callback):
        # 调用父类的构造函数
        super().__init__()

        # 保存提交按钮的回调函数
        self.on_submit_callback = on_submit_callback

        # 初始化UI界面
        self.initUI()

    def initUI(self):
        # 设置窗口标题
        self.setWindowTitle('Gemini API Interface')

        # 设置窗口大小
        self.resize(1000, 800)

        # 设置窗口图标（请替换为实际的图标路径）
        self.setWindowIcon(QIcon('path/to/your/icon.png'))

        # 设置主题为浅色主题
        setTheme(Theme.LIGHT)

        # 创建顶部导航栏和堆叠窗口
        self.pivot = Pivot(self)
        self.stackedWidget = QStackedWidget(self)
        self.vBoxLayout = QVBoxLayout(self)

        # 设置全局字体
        font = QFont('微软雅黑', 11)

        # 创建模型选择下拉框并设置字体和选项
        self.model_combo = ComboBox()
        self.model_combo.setFont(font)
        self.model_combo.addItems(['gemini-1.0-pro', 'gemini-1.5-flash', 'gemini-1.5-pro'])

        # 创建提示输入框并设置字体和占位符文本
        self.prompt_input = LineEdit()
        self.prompt_input.setFont(font)
        self.prompt_input.setPlaceholderText('在此输入...')

        # 创建提交按钮并设置字体及点击事件连接函数
        self.submit_button = PrimaryPushButton('提交')
        self.submit_button.setFont(font)
        self.submit_button.clicked.connect(self.on_submit)

        # 创建结果显示框并设置字体和只读属性
        self.result_text = TextEdit()
        self.result_text.setFont(font)
        self.result_text.setReadOnly(True)

        # 初始化主界面
        self.main_widget = self.create_main_interface()

        # 添加不同的子界面
        self.songInterface = QLabel('测试界面1', self)
        self.albumInterface = QLabel('测试界面2', self)
        self.artistInterface = QLabel('设置界面', self)
        self.addSubInterface(self.main_widget, '主界面', '主界面')
        self.addSubInterface(self.songInterface, '测试界面1', '测试界面1')
        self.addSubInterface(self.albumInterface, '测试界面2', '测试界面2')
        self.addSubInterface(self.artistInterface, '设置界面', '设置')

        # 设置主布局的边距和添加部件
        self.vBoxLayout.setContentsMargins(30, 0, 30, 30)
        self.vBoxLayout.addWidget(self.pivot, 0, Qt.AlignHCenter)
        self.vBoxLayout.addWidget(self.stackedWidget)
        
        # 创建主容器并设置布局
        container = QWidget()
        container.setLayout(self.vBoxLayout)
        self.setCentralWidget(container)

        # 设置初始显示的页面
        self.stackedWidget.setCurrentWidget(self.main_widget)
        self.pivot.setCurrentItem('mainInterface')

    def create_main_interface(self):
        # 创建主界面的布局并设置边距和间距
        main_layout = QVBoxLayout()
        main_layout.setContentsMargins(20, 20, 20, 20)
        main_layout.setSpacing(20)

        font = QFont('微软雅黑', 11)

        # 创建并添加模型选择标签和下拉框
        model_label = QLabel('请选择要使用的模型：')
        model_label.setFont(font)
        main_layout.addWidget(model_label)
        main_layout.addWidget(self.model_combo)

        # 创建并添加提示输入标签和输入框
        prompt_label = QLabel('请输入提示语：')
        prompt_label.setFont(font)
        main_layout.addWidget(prompt_label)
        main_layout.addWidget(self.prompt_input)

        # 添加提交按钮
        main_layout.addWidget(self.submit_button)

        # 创建并添加结果显示标签和文本框
        result_label = QLabel('结果：')
        result_label.setFont(font)
        main_layout.addWidget(result_label)
        main_layout.addWidget(self.result_text)

        # 创建主界面部件并设置布局
        main_widget = QWidget()
        main_widget.setLayout(main_layout)

        return main_widget

    def addSubInterface(self, widget, objectName, text):
        # 设置子界面的对象名并添加到堆叠窗口中
        widget.setObjectName(objectName)
        self.stackedWidget.addWidget(widget)

        # 使用唯一的对象名作为路由键添加到导航栏中
        self.pivot.addItem(routeKey=objectName, text=text, onClick=lambda: self.stackedWidget.setCurrentWidget(widget))

    def on_submit(self):
        # 获取提示输入和模型选择的文本
        prompt = self.prompt_input.text()
        model = self.model_combo.currentText()

        if prompt and model:
            # 调用回调函数处理输入并更新结果
            try:
                result = self.on_submit_callback(prompt, model)
                if result:
                    self.result_text.setPlainText(result)
                    self.show_success("成功")
            except Exception as e:
                self.show_error(f"提交过程中发生错误：{e}")
        else:
            self.show_error('输入错误，请输入提示语并选择模型')

    def update_result_text(self, text):
        # 更新结果显示框的文本
        self.result_text.setPlainText(text)

    def show_error(self, message):
        # 显示错误信息
        InfoBar.error(title="错误", content=message, position=InfoBarPosition.TOP, duration=3000, parent=self)

    def show_success(self, message):
        # 显示成功信息
        InfoBar.success(title="Gemini", content=message, position=InfoBarPosition.TOP, duration=3000, parent=self).show()
