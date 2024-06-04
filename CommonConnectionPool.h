#pragma once
#include <string>
#include <queue>
#include <mutex>
#include "Connection.h"
#include <iostream>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
using namespace std;

/*
* ʵ�����ӳع���ģ��
*/

class ConnectionPool {
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();
	// ���ⲿ�ṩ�ӿڣ������ӳ��л�ȡһ�����õĿ�������
	shared_ptr<Connection> getConnection();

private:
	ConnectionPool(); // ����#1 ���캯��˽�л�

	bool loadConfigFile(); // �������ļ��м���������

	// �����ٶ������߳��У�ר�Ÿ�������������
	void produceConnectionTask();

	void scannerConnectionTask();

	string _ip; // mysql��IP��ַ
	unsigned short _port; // MySQL �Ķ˿ںţ� 3306
	string _username; // MySQL��¼�û���
	string _password; // MySQL��½����
	string _dbname; // ���ӵ����ݿ�����
	int _initSize; // ���ӳصĳ�ʼ������
	int _maxSize; // ���ӳص����������
	int _maxIdleTime; // ���ӳص�������ʱ��
	int _connectionTimeout; // ���ӳػ�ȡ���ӵĳ�ʱʱ��

	queue<Connection*> _connectionQue; // �洢MySQL���ӵĶ���
	mutex _queueMutex; // ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt; // ��¼������������connection���ӵ�������
	condition_variable cv; // ���������������������������̺߳����������̵߳�ͨ��
};