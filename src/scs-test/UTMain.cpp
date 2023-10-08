// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#include <string>
#include <gflags/gflags.h>
#include <glog/logging.h>

// global
#include "GlobalVariables.hpp"

// test case header
#include "entity/test_scs_config.hpp"
#include "entity/test_scs_node.hpp"
#include "entity/test_scs_graph.hpp"
#include "function/test_scs_function.hpp"

// declare default flag values
DEFINE_string(app_name, "Supply Chain Simulator", "Application name");

// -> log
DEFINE_string(y_log_dir, ".", "The directory where log file output.");
DEFINE_int32(y_logbufsecs, 0, "设置可以缓冲日志的最大秒数, 0指实时输出");
DEFINE_bool(y_logtostderr, false, "TRUE:标准输出,FALSE:文件输出");
DEFINE_bool(y_alsologtostderr, true, "除了日志文件之外是否需要标准输出");
DEFINE_bool(y_colorlogtostderr, false, "标准输出带颜色");
DEFINE_int32(y_max_log_size, 10, "日志文件大小(单位: MB)");
DEFINE_bool(y_stop_logging_if_full_disk, true, "磁盘满时是否记录到磁盘");
DEFINE_string(y_log_filename_extension, ".log", "Specify an 'extension' added to the filename");
// -> debug
DEFINE_bool(debug, false, "Debug flag");


// declare debug flag
bool isDebug;

/**
 * init environment
 */
void initEnv(int argc, char *argv[])
{

    // parse paramaters
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    isDebug = FLAGS_debug;

    // assign log config
    FLAGS_log_dir = FLAGS_y_log_dir;
    FLAGS_logbufsecs = FLAGS_y_logbufsecs;
    FLAGS_logtostderr = FLAGS_y_logtostderr;
    FLAGS_alsologtostderr = FLAGS_y_alsologtostderr;
    FLAGS_colorlogtostderr = FLAGS_y_colorlogtostderr;
    FLAGS_max_log_size = FLAGS_y_max_log_size;
    FLAGS_stop_logging_if_full_disk = FLAGS_y_stop_logging_if_full_disk;
    google::SetLogFilenameExtension(FLAGS_y_log_filename_extension.data());
    google::InitGoogleLogging(FLAGS_app_name.data());

}

/**
 * main
 */
int main(int argc, char *argv[])
{
    // application name
    std::string programName = "Supply Chain Simulator";

    // init environment
    initEnv(argc, argv);

    // log
    LOG(INFO) << programName;

    // run tese
    scs::test::entity::config::test_all();
    scs::test::entity::node::test_all();
    scs::test::entity::graph::test_all();
    scs::test::function::func::test_all();

    // output all logs
    google::FlushLogFiles(google::GLOG_INFO);

    return EXIT_SUCCESS;
}
