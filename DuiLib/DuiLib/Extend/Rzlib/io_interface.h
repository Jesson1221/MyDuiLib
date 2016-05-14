#ifndef io_interface_h
#define io_interface_h


#pragma once
#include <tchar.h>
#include <vector>
#include <string>

namespace em_utility
{
#ifndef FILE_BEGIN
#define FILE_BEGIN        0
#endif

#ifndef FILE_CURRENT
#define FILE_CURRENT    1
#endif

#ifndef FILE_END
#define FILE_END        2
#endif

	//IO�ӿ�
	class RZ_DLL_API io_base
	{
	public:
		static const int NORMAL_SUCCESS = 0;
		static const int NORMAL_FAILED = -1;
		io_base() { }
		virtual ~io_base() { };
		virtual int open(const TCHAR* p_name, bool b_readonly) = 0;			//��һ�����ڵ��ļ�
		virtual int close() = 0;										//�ر��ļ�
		// read / write, will change current position
		//return : 0 for success, -1 for failed
		virtual int read(void* p_buffer, unsigned int n_bytes_2_read, unsigned int* p_bytes_read) = 0;					//�ӵ�ǰλ�ö����ݵ�������
		virtual int write(const void* p_buffer, unsigned int n_bytes_2_write, unsigned int* p_bytes_written) = 0;		//�ѻ���������д�뵱ǰλ��
		// seek
		virtual int seek(int n_distance, unsigned int n_move_mode) = 0;			//��ǰָ�붨λ
		// creation / destruction
		virtual int create(const TCHAR* p_name) = 0;			//����һ���ļ�
		virtual int destroy() = 0;											//ɾ��һ���ļ�
		virtual int set_EOF() = 0;											//�ضϻ������ļ�
		virtual int get_position() = 0;									//ȡ�õ�ǰλ��
		virtual int get_size() = 0;											//ȡ���ļ���С
		virtual int get_name(TCHAR* p_buffer) = 0;				//ȡ���ļ���
		virtual bool is_open() = 0;										//�Ƿ��
		virtual int flush() = 0;												//����ͬ��
	};

	//λ����Ϣ
	struct RZ_DLL_API pos_info
	{
	public:
		pos_info(unsigned int n_begin = 0, unsigned int n_len = 0);
		virtual ~pos_info();
		unsigned int get_begin() const;
		unsigned int get_len() const;
		unsigned int get_end() const;
		void set_info(unsigned int n_begin, unsigned int n_len);
		bool valid() const;
		unsigned int size() const;
		bool is_sub_pos(const pos_info& pos) const;
		bool is_equal_pos(const pos_info& pos) const;
	private:
		unsigned int mn_begin;		//���ݿ�ʼλ��
		unsigned int mn_len;				//���ݳ���
	};

	typedef std::vector<pos_info> position_container;
	typedef position_container::iterator position_iter;

	pos_info::pos_info(unsigned int n_begin, unsigned int n_len)
	{
		mn_begin = n_begin;
		mn_len = n_len;
	}

	pos_info::~pos_info()
	{
	}

	unsigned int pos_info::get_begin() const
	{
		return mn_begin;
	}

	unsigned int pos_info::get_len() const
	{
		return mn_len;
	}

	unsigned int pos_info::get_end() const
	{
		return get_begin() + get_len();
	}

	void pos_info::set_info(unsigned int n_begin, unsigned int n_len)
	{
		mn_begin = n_begin;
		mn_len = n_len;
	}

	bool pos_info::valid() const
	{
		return mn_len > 0;
	}

	unsigned int pos_info::size() const
	{
		return get_len();
	}

	bool pos_info::is_sub_pos(const pos_info& pos) const
	{
		bool b_result = false;
		if (pos.get_begin() >= get_begin() && pos.size() <= size() && pos.get_end() <= get_end())
			b_result = true;
		return b_result;
	}

	bool pos_info::is_equal_pos(const pos_info& pos) const
	{
		return pos.get_begin() == get_begin() && pos.size() == size();
	}

}
#endif//io_interface_h