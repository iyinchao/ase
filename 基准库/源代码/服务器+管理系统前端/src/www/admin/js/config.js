Config = {
    FILE_SRORE:'../../../../filestore/',
    TABLE_LANG:{
        processing:     "处理中...",
        search:         "搜索:",
        lengthMenu:     "显示 _MENU_ 项结果",
        info:           "显示第 _START_ 至 _END_ 项结果，共 _TOTAL_ 项",
        infoEmpty:      "显示第 0 至 0 项结果，共 0 项",
        infoFiltered:   "(由 _MAX_ 项结果过滤)",
        infoPostFix:    "",
        loadingRecords: "载入中...",
        zeroRecords:    "没有匹配结果",
        emptyTable:     "表中数据为空",
        paginate: {
            first:      "首页",
            previous:   "上页",
            next:       "下页",
            last:       "末页"
        },
        aria: {
            sortAscending:  ": 以升序排列此列",
            sortDescending: ": 以降序排列此列"
        }
    },
    API_LIST:{
        SCENE:{
            client_download:{
                display_name:"客户端下载场景文件",
                op:"client_download",
                data:{"s_id":"00000000-83e7-498f-bc5b-1f4e84f074f3","test":"yes"}
            },
            client_download_admin:{
                display_name:"服务器下载场景文件",
                op:"client_download",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3","test":"yes", "admin_op":true}
            },
            get_meta_by_id:{
                display_name:"获取元数据",
                op:"get_meta_by_id",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3"}
            },
            get_new_b_id:{
                display_name:"获得新UUID",
                op:"get_new_b_id"
            },
            client_browser:{
                display_name:"场景信息浏览(并过滤)",
                op:"client_browser",
                data:{"page_now":"0","scene_per_page":"6","tag":[3]}
            },
            client_browser_all:{
                display_name:"场景信息浏览(全部)",
                op:"client_browser",
                data:{"page_now":"0","scene_per_page":"-1"}
            },
            client_get_thumb:{
                display_name:"获取缩略图",
                op:"client_get_thumb",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3"}
            },
            add:{
                display_name:"新增场景",
                op:"add",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3"}
            },
            update_one:{
                display_name:"更新单个场景",
                op:"update_one",
                data:{"s_id":"00000000-83e7-498f-bc5b-1f4e84f074f3"}
            },
            delete_one:{
                display_name:"删除单个场景",
                op:"delete_one",
                data:{"s_id":"00000000-83e7-498f-bc5b-1f4e84f074f3"}
            }
        },
        TAG:{
            get_all_tags:{
                display_name:"获取全部标签信息",
                op:"get_all_tags"
            },
            get_one_scene_tags:{
                display_name:"获取单个场景的标签信息",
                op:"get_all_tags",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3"}
            },
            update_tag_scene:{
                display_name:"更新场景标签",
                op:"update_tag_scene",
                data:{"s_id":"a90cb734-83e7-498f-bc5b-1f4e84f074f3"}
            },
            update_tag_scene_noecho:{
                display_name:"更新场景标签(安静模式)",
                op:"update_tag_scene"
            }
        },
        USER:{
            admin_login:{
                display_name:"管理员登录",
                op:"admin_login"
            },
            admin_logout:{
                display_name:"管理员登出",
                op:"admin_logout"
            }
        }
    }
};