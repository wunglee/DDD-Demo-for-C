cc_library(
  name = "framework_components",
  srcs = [
    "src/framework_components/requestion_filters/static_init.cpp",
    "src/framework_components/domain_event/publish_subscribe_service.cpp",
    "src/framework_components/domain_event/memory_publish_subscribe_service.cpp",
    "src/framework_components/naming_service/static_init.cpp",
    ],
  includes = ["."],
  hdrs = [
  ],
  deps = [
    "//mm3rd/boost-1.69:boost_system"
  ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",
  ],
  visibility = ["//visibility:public"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
  name = "framework_components_test",
  srcs = ["test/framework_test/framework_test.cpp"],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",

  ],
  deps = [
    ":framework_components", 
    "//mm3rd/gtest",],
)



cc_library(
  name = "bc_user",
  srcs = [
    "src/bc/user/static_init.cpp",
    ],
  includes = ["."],
  hdrs = [
  ],
  deps = [
    "//mm3rd/boost-1.69:boost_system",
    ":framework_components",
  ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "user_test",
  srcs = [
    "test/unit_test/bc/user/static_init.cpp",
    "test/unit_test/bc/user/user_unit_test.cpp"
    ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",

  ],
  deps = [
    ":bc_user", 
    "//mm3rd/gtest",],
)



cc_library(
  name = "bc_fund",
  srcs = [
    "src/bc/fund/static_init.cpp",
    ],
  includes = ["."],
  hdrs = [
  ],
  deps = [
    "//mm3rd/boost-1.69:boost_system",
    ":framework_components",
  ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "fund_test",
  srcs = [
    "test/unit_test/bc/fund/static_init.cpp",
    "test/unit_test/bc/fund/fund_unit_test.cpp"
    ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",

  ],
  deps = [
    ":bc_fund", 
    "//mm3rd/gtest",],
)



cc_library(
  name = "bc_transfer",
  srcs = [
    "src/bc/transfer/static_init.cpp",
    ],
  includes = ["."],
  hdrs = [
  ],
  deps = [
    "//mm3rd/boost-1.69:boost_system",
    ":framework_components",
  ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "transfer_test",
  srcs = [
    "test/unit_test/bc/transfer/static_init.cpp",
    "test/unit_test/bc/transfer/transfer_unit_test.cpp"
    ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",

  ],
  deps = [
    ":bc_transfer", 
    "//mm3rd/gtest",],
)



cc_binary(
  name = "integration_test",
  srcs = [
    "test/integration_test/require_flow_test.cpp",
    ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",

  ],
  deps = [
    ":bc_transfer", 
    ":bc_user", 
    ":bc_fund", 
    "//mm3rd/gtest",],
)




#  for svrkit
cc_library(
  name = "framework_components_svrkit",
  srcs = [
    "src/framework_components/idempotent/mysql_idempotent_manager.cpp",
    "src/framework_components/local_transaction/mysql_transaction_manager.cpp",
    "src/framework_components/domain_event/mysql_publish_subscribe_service.cpp",
    ],
  includes = ["."],
  hdrs = [
  ],
  deps = [
    ":framework_components",
    "//mm3rd/fmt:fmt",
    "//appplatform/export_lib_tlinux:dal_set",
  ],
  copts = [
    "-std=c++11",
    "-Wall",
    "-Werror",
    "-Wextra",
  ],
  visibility = ["//visibility:public"],
)