#include "mysqlc.h"



MySQLC::MySQLC() {
    mysql_thread_init() ;
	mysql_init(&mysql);
}


MySQLC::~MySQLC() {
	disConnect();
	mysql_thread_end();
}


bool MySQLC::connect(std::string host, std::string user, std::string password, std::string db, int port) {
	if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port, NULL, 0)) {
        std::cout << mysql_error(&mysql) << std::endl ;
		return false;
	}
	return true;
}

void MySQLC::disConnect() {
	mysql_close(&mysql);
}


bool MySQLC::query(std::string sql) {
	if (!mysql_query(&mysql, sql.c_str())) {
		return true ;
	}
	return false ;
}


bool MySQLC::query(std::string sql, std::function<bool(MYSQL_ROW)> f, std::function<void(void)> empty) {
	if (!mysql_query(&mysql, sql.c_str())) {
		if (nullptr != (res = mysql_store_result(&mysql))) {
			bool retVal = true;
			if (mysql_num_rows(res)) {
				while ((row = mysql_fetch_row(res)) != NULL) {
					retVal = f(row);
				}
			}else {
				if (empty) {
					empty();
				}
			}
			mysql_free_result(res);
			return retVal;
        }else {
            return false ;
        }
	}
	else {
		std::cout << mysql_error(&mysql) << " == " << sql << std::endl;
		return false;
	}
}

std::vector<std::string> MySQLC::getValue(std::string column)
{
	return std::vector<std::string>();
}
