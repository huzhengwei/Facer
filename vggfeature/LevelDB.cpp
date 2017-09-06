/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "LevelDB.h"

#include <functional>
#include <queue>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath> 
#include <numeric>

namespace Facer
{
	LevelDB::LevelDB(const std::string db_dir = "../DataBase/")
	{
		leveldb::Options options;
		options.create_if_missing = true;
		status_ = leveldb::DB::Open(options, db_dir, &ldb_);
	}
	LevelDB::~LevelDB()
	{
		delete ldb_;
	}
	bool LevelDB::insert(const std::vector<float>& feature, const std::string& name, const std::string& imgname)
	{
		std::string value;
		Serial2String(feature, name, value);
		leveldb::WriteOptions write_options;
		write_options.sync = true;
		status_ = ldb_->Put(write_options, imgname, value);
		return true;
	}
	bool LevelDB::find(const std::vector<float>& feature, std::string& name, std::string& imgname) const
	{
		std::string key, value, db_name;
		std::vector<float> db_feature;
		float dis , min_dis = min_dis_;
		leveldb::Iterator* it = ldb_->NewIterator(leveldb::ReadOptions());
		for (it->SeekToFirst(); it->Valid(); it->Next()) {
			key = it->key().ToString();
			value =  it->value().ToString();
			ParseFromString(value, feature.size(), db_feature, db_name);
			dis = vectors_distance(feature, db_feature);
			if (dis < min_dis)
			{
				name = db_name;
				imgname = key;
				min_dis = dis;
			}
		}
		
		delete it;
		return min_dis < min_dis_;
	}
	void LevelDB::Serial2String(const std::vector<float>& feature, const std::string& name, std::string& str) const
	{
		str = std::string((char*)&feature[0], feature.size()*sizeof(float)) + name;
	}
	void LevelDB::ParseFromString(const std::string& str, int size, std::vector<float>& feature, std::string& name) const
	{
		float* start = (float*)str.c_str();
		feature = std::vector<float>(start, start +size);
		name = str.substr(size*sizeof(float));
	}

	// Computes the distance between two std::vectors
	template <typename T>
	float	vectors_distance(const std::vector<T>& a, const std::vector<T>& b)
	{
		std::vector<double>	auxiliary;

		std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),//
			[](T element1, T element2) {return pow((element1 - element2), 2);});
		auxiliary.shrink_to_fit();

		return  std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0);
	} // end template vectors_distance
}