"""
描    述：与Gemini进行交流

当前版本：v1.0
作   者：YRQ
完成日期：2024/6/27

这段代码通过一个图形用户界面（GUI）应用与Gemini服务进行交互。
它接收用户输入的提示信息，调用Gemini生成响应内容，并在窗口中显示结果。同时，代码还记录了交互过程中的日志信息。
"""
# ---------------------------------------------------------------------------------------------------------------------
# 导入所需的库和模块
import google.generativeai as genai 
import time 
import json  
import os 
import Math_Basic  # 自定义的数学基本操作模块
from gui import GeminiApp  # 自定义的 GUI 应用程序模块
from PyQt5.QtWidgets import QApplication 
# ---------------------------------------------------------------------------------------------------------------------

# 设置代理端口号，我不设置这个会报错
os.environ['http_proxy'] = 'http://127.0.0.1:80'
os.environ['https_proxy'] = 'http://127.0.0.1:80'
os.environ['all_proxy'] = 'http://127.0.0.1:80'

# 设置 API 密钥
genai.configure(api_key='your_api_key')

# 设置希望 Gemini 调用的函数，包括加法、减法、乘法和除法。如果要使用请在genai.GenerativeModal()里面添加tools=tools_used
#tools_used = [Math_Basic.add, Math_Basic.subtract, Math_Basic.multiply, Math_Basic.divide]

# 定义函数以获取 Gemini 生成的代码
def get_gemini_code(prompt, model_name):
    # 使用指定的模型名称创建生成模型实例，并设置生成配置
    model_used = genai.GenerativeModel(model_name=model_name, generation_config={"temperature": 0})

    try:
        # 记录开始处理时间
        start_time = time.time()
        # 开始对话，并启用自动函数调用
        chat = model_used.start_chat(enable_automatic_function_calling=True)
        # 发送带有历史记录的消息并获取响应
        response = chat.send_message(prompt)
        # 记录结束处理时间
        end_time = time.time()
    except Exception as e:
        # 如果发生异常，返回错误信息
        return None, None, str(e)

    # 记录处理完成时间和处理时长
    response_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
    processing_time = end_time - start_time

    # 获取本次请求使用的 token 数量
    tokens_used = model_used.count_tokens(prompt).total_tokens

    # 记录日志数据
    log_data = {
        'model': model_name,
        'request_time': response_time,
        'response_time': response_time,
        'processing_time': processing_time,
        'user_input': prompt,
        'tokens_used': tokens_used
    }
    # 将日志数据写入文件
    with open('gemini_log.json', 'a') as log_file:
        log_file.write(json.dumps(log_data) + '\n')

    # 查看对话流程及函数调用，可以看到 Gemini 是否调用了 tools_used 中的函数
    for content in chat.history:
        print(content.role, "->", [type(part).to_dict(part) for part in content.parts])
        print("-" * 100)

    # 返回响应、使用的 token 数量及错误信息（如果有）
    return response, tokens_used, None

# 定义函数以处理命令
def process_command(prompt, model_name, window):
    # 获取 Gemini 生成的代码
    response, tokens_used, error = get_gemini_code(prompt, model_name)

    # 如果有错误，显示错误信息
    if error:
        window.show_error(f"失败：{error}")
        return None
    else:
        # 更新结果文本并显示在窗口中
        result_text = f"以下为 Gemini 生成内容：\n\n{response.text}\n\n本次对话使用了 {tokens_used} 个 token"
        window.update_result_text(result_text)
        return result_text

# 主程序入口
if __name__ == "__main__":
    # 创建 PyQt 应用程序实例
    app = QApplication([])
    # 创建 GeminiApp 实例，并设置提交回调函数
    window = GeminiApp(on_submit_callback=lambda prompt, model_name: process_command(prompt, model_name, window))
    # 显示窗口
    window.show()
    # 进入应用程序主循环
    app.exec_()
