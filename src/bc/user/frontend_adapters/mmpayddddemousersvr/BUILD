load("/mmpay_git/mmpay_comm/component_export/mmpay_pbtools/sbin/wxp_sktools", "wxp_skproto2service")
load("/mmpay_git/mmpay_comm/component_export/mmpay_pbtools/sbin/wxp_sktools", "wxp_skproto2test")


wxp_skproto2service(
    name = "sk_mmpayddddemousersvrservice_pb_h",
    srcs = [
        "//mmpaygitgateway/mmpay_comm/service_export_gen/XWatt-P/XWatt/domain/mmpayddddemousersvr:proto/mmpayddddemousersvr.proto",
    ],
    outs = [
        "src/gen_code/skproto/sk_mmpayddddemousersvrdispatcher.pb.cpp",
        "src/gen_code/skproto/sk_mmpayddddemousersvrdispatcher.pb.h",
        "src/gen_code/skproto/sk_mmpayddddemousersvrservice.pb.cpp",
        "src/gen_code/skproto/sk_mmpayddddemousersvrservice.pb.h",
    ],
    extra_args = '-n'
)

wxp_skproto2test(
    name = "sk_mmpayddddemousersvrtest_pb_h",
    srcs = [
        "//mmpaygitgateway/mmpay_comm/service_export_gen/XWatt-P/XWatt/domain/mmpayddddemousersvr:proto/mmpayddddemousersvr.proto",
    ],
    outs = [
        "test/gen_code/skproto/sk_mmpayddddemousersvrtest.pb.cpp",
        "test/gen_code/skproto/sk_mmpayddddemousersvrtest.pb.h",
    ],
    extra_args = '-n'
)

cc_binary(
  name = "mmpayddddemousersvr",
  srcs = [
      "src/code/mmpayddddemousersvrmain.cpp",
      "src/code/mmpayddddemousersvrserviceimpl_pb.cpp",
      "src/code/mmpayddddemousersvrconfig.cpp",
      "src/code/mmpayddddemousersvrserver.h",
      "src/code/mmpayddddemousersvrserviceimpl_pb.h",
      "src/gen_code/skproto/sk_mmpayddddemousersvrdispatcher.pb.cpp",
      "src/gen_code/skproto/sk_mmpayddddemousersvrservice.pb.cpp",
      "src/gen_code/skproto/sk_mmpayddddemousersvrdispatcher.pb.h",
      "src/gen_code/skproto/sk_mmpayddddemousersvrservice.pb.h",
      # XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-srcs][自定义源文件]
      # ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
      # ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
      # XWATT-TAG-END:[flow][mmpayddddemousersvr-srcs][自定义源文件]            
  ],
  includes = [".", "src/gen_code/skproto"],
  deps = [

                  "//mmpay_git/mmpay_XWatt-P/XWatt/DDD-Demo:bc_user",
                  "//mmpay_git/mmpay_XWatt-P/XWatt/DDD-Demo:framework_components_svrkit",
                    "//mm3rd/boost-1.69:boost_system",

      "//comm2/svrkit:svrkitepoll",
      "//comm2/svrkit:svrkit_pb",
      "//comm2/tlvpickle:skbuiltintype",
      "//mmtenpay/mmpaylog:mmpaylogutils",
      "//mmpay/mmpayxwatt/xwatt/log:log",
      "//mmpay/mmpayxwatt/xwatt/oss:oss",
      "//mmpay/mmpayxwatt/xwatt/mmdata:mmdata_reporter",
      "//mmpay_git/mmpay_comm/component_export/mmpaylogapi:mmpaylogapi",
      "//mmtenpay/mmpaybasic/mmpayerrorcode/mmpayerrorapi:mmpayerrorapi",
      "//mmpaygitgateway/mmpay_comm/service_export_gen/XWatt-P/XWatt/domain/mmpayddddemousersvr:mmpayddddemousersvrclient",
      

      # XWATT-TAG-BEGIN:[flow][xwatt-deps-for-component][其他生成器的依赖]

      # XWATT-TAG-END:[flow][xwatt-deps-for-component][其他生成器的依赖]   

      # XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-deps][自定义依赖]
      # ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

      # ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
      # XWATT-TAG-END:[flow][mmpayddddemousersvr-deps][自定义依赖]        

  ],
  # XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-opts][自定义源文件]
  # ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
  copts = [
      "-std=c++11"
  ],
  linkopts = [
  ],
  # ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  # XWATT-TAG-END:[flow][mmpayddddemousersvr-opts][自定义源文件]    

)

cc_binary(
  name = "mmpayddddemousersvr_tools_pb",
  srcs = [
      "test/code/mmpayddddemousersvr_tools_pb.cpp",
      "test/code/mmpayddddemousersvrtestimpl_pb.cpp",
      "test/code/mmpayddddemousersvrtestimpl_pb.h",
      "test/gen_code/skproto/sk_mmpayddddemousersvrtest.pb.cpp",
      "test/gen_code/skproto/sk_mmpayddddemousersvrtest.pb.h",
  ],
  includes = [".", "test/gen_code/skproto"],
  deps = [
      "//mmpaygitgateway/mmpay_comm/service_export_gen/XWatt-P/XWatt/domain/mmpayddddemousersvr:mmpayddddemousersvrclient",
  ],
  copts = [
      "-std=c++11"
  ],
  linkopts = [
  ],
)

# XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-custom][]
# ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

# ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
# XWATT-TAG-END:[flow][mmpayddddemousersvr-custom][]    

