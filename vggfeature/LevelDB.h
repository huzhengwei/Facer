/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_LEVELDB_H
#define FACER_LEVELDB_H

#include "DB.h"

#include <string>
#include <leveldb/db.h>

namespace Facer
{
	class LevelDB : public DB
	{
	public:
		LevelDB(const std::string db_dir);
		~LevelDB();
		bool insert(const std::vector<float>& feature, const std::string& name, const std::string& imgname) override;
		bool find(const std::vector<float>& feature, std::string& name, std::string& imgname) const override;
	private:
		void Serial2String(const std::vector<float>& feature, const std::string& name, std::string& str) const;
		void ParseFromString(const std::string& str, int size, std::vector<float>& feature, std::string& name) const;
		leveldb::DB* ldb_;
		leveldb::Status status_;
		const float min_dis_ = 400 * 400;
	};
	template <typename T>
	float	vectors_distance(const std::vector<T>& a, const std::vector<T>& b);
}
#endif