# 个人的测试Cocos与相关功能的实例项目：

* 添加类实现平台差异化类
* 添加JNI Android调用
* 添加多线程访问数据的方法，lock.unlock
* 添加如何让Cocos GL线程执行子线程里的一个方法，performFunctionInCocosThread
* 添加实现，如果外部判断一个类是否析构，在C+11 lambda函数，回调，访问类成员时非常有用
* 添加主动Crash上传Bugly的测试方法
* 添加测试Android在上下文丢失时，监听的方法调用，可以游戏触发业务需要重新初始化相关的方法 EVENT_RENDERER_RECREATED
* 添加一些错误的方法引用，与正确与否，不要强行使用全局指针指向一个不存在的已经析构的类地址
