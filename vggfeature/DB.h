/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_DB_H
#define FACER_DB_H

#include <string>
#include <vector>

namespace Facer
{
	class DB
	{
	public:
		DB();
		virtual ~DB();
		virtual bool insert(const std::vector<float>& feature, const std::string& name, const std::string& imgname) = 0;
		virtual bool find(const std::vector<float>& feature, std::string& name, std::string& imagename) const = 0;
	private:

	};
}
#endif
