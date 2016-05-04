
#include <pthread.h>
#pragma comment(lib,"x64/pthreadVC2.lib")


class TC_Runable
{
public:
	virtual ~TC_Runable(){};
	virtual void run() = 0;
};

class TC_ThreadControl;
class TC_ThreadLock;

/**
* �̻߳���.
* �̻߳��࣬�����Զ����̼̳߳��ڸ��࣬ͬʱʵ��run�ӿڼ���,
* ����ͨ��TC_ThreadContorl�����̡߳�
*/
class TC_Thread : public TC_Runable
{
public:

	/**
	* @brief  ���캯��
	*/
	TC_Thread() : : _running( false), _tid(-1)
	{}

	/**
	* @brief  ��������
	*/
	virtual ~TC_Thread(){};

	/**
	* @brief  �߳�����
	*/
	TC_ThreadControl start(){
		TC_ThreadLock::Lock sync(_lock);
		if(_running)
	    {
	        throw TC_ThreadThreadControl_Exception("[TC_Thread::start] thread has start");
	    }
	    int ret = pthread_create(&_tid , 0, ( void *(*)( void *))& threadEntry, ( void *) this);

	    if(ret != 0)
	    {
	        throw TC_ThreadThreadControl_Exception("[TC_Thread::start] thread start error", ret);
	    }
	    _lock.wait();

	    return TC_ThreadControl(_tid);
	}

	/**
	* @brief  ��ȡ�߳̿�����.
	*
	* @return ThreadControl
	*/
	TC_ThreadControl getThreadControl() const{
		return TC_ThreadControl(_tid);
	}

	/**
	* @brief  �߳��Ƿ���.
	*
	* @return bool ����true�����򷵻�false
	*/
	bool isAlive() const{
		return _running;
	}

	/**
	* @brief  ��ȡ�߳�id.
	*
	* @return pthread_t �߳�id
	*/
	pthread_t id() { return _tid; }

protected:

	/**
	* @brief  ��̬����, �߳����.
	*
	* @param pThread �̶߳���
	*/
	static void threadEntry(TC_Thread *pThread){
		pThread->_running = true;

		{
        	TC_ThreadLock::Lock sync(pThread-> _lock);
        	pThread-> _lock.notifyAll();
    	}
    	
    	try
    	{
    		pThread->run();
    	}
    	catch(...)
    	{
    		pThread-> _running = false;
    		throw;
    	}
    	pThread->_running = false;
	}

	/**
	* @brief  ����
	*/
	virtual void run() = 0;

protected:
	/**
	* �Ƿ�������
	*/
	bool            _running;

	/**
	* �߳�ID
	*/
	pthread_t      _tid;

	/**
	* �߳���
	*/
	TC_ThreadLock   _lock;
};
