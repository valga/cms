do

    local commands = {
        [1000] = "LOGIN_REQ",
        [1001] = "LOGIN_RSP",
        [1002] = "LOGOUT_RSP",
        [1003] = "FORCELOGOUT_REQ",
        [1004] = "FORCELOGOUT_RSP",
        [1006] = "KEEPALIVE_REQ",
        [1007] = "KEEPALIVE_RSP",
        [1020] = "SYSINFO_REQ",
        [1021] = "SYSINFO_RSP",
        [1040] = "CONFIG_SET",
        [1041] = "CONFIG_SET_RSP",
        [1042] = "CONFIG_GET",
        [1043] = "CONFIG_GET_RSP",
        [1044] = "DEFAULT_CONFIG_GET",
        [1045] = "DEFAULT_CONFIG_GET_RSP",
        [1046] = "CONFIG_CHANNELTILE_SET",
        [1047] = "CONFIG_CHANNELTILE_SET_RSP",
        [1048] = "CONFIG_CHANNELTILE_GET",
        [1049] = "CONFIG_CHANNELTILE_GET_RSP",
        [1050] = "CONFIG_CHANNELTILE_DOT_SET",
        [1051] = "CONFIG_CHANNELTILE_DOT_SET_RSP",
        [1052] = "SYSTEM_DEBUG_REQ",
        [1053] = "SYSTEM_DEBUG_RSP",
        [1360] = "ABILITY_GET",
        [1361] = "ABILITY_GET_RSP",
        [1400] = "PTZ_REQ",
        [1401] = "PTZ_RSP",
        [1410] = "MONITOR_REQ",
        [1411] = "MONITOR_RSP",
        [1412] = "MONITOR_DATA",
        [1413] = "MONITOR_CLAIM",
        [1414] = "MONITOR_CLAIM_RSP",
        [1420] = "PLAY_REQ",
        [1421] = "PLAY_RSP",
        [1422] = "PLAY_DATA",
        [1423] = "PLAY_EOF",
        [1424] = "PLAY_CLAIM",
        [1425] = "PLAY_CLAIM_RSP",
        [1426] = "DOWNLOAD_DATA",
        [1430] = "TALK_REQ",
        [1431] = "TALK_RSP",
        [1432] = "TALK_CU_PU_DATA",
        [1433] = "TALK_PU_CU_DATA",
        [1434] = "TALK_CLAIM",
        [1435] = "TALK_CLAIM_RSP",
        [1440] = "FILESEARCH_REQ",
        [1441] = "FILESEARCH_RSP",
        [1442] = "LOGSEARCH_REQ",
        [1443] = "LOGSEARCH_RSP",
        [1444] = "FILESEARCH_BYTIME_REQ",
        [1445] = "FILESEARCH_BYTIME_RSP",
        [1450] = "SYSMANAGER_REQ",
        [1451] = "SYSMANAGER_RSP",
        [1452] = "TIMEQUERY_REQ",
        [1453] = "TIMEQUERY_RSP",
        [1460] = "DISKMANAGER_REQ",
        [1461] = "DISKMANAGER_RSP",
        [1470] = "FULLAUTHORITYLIST_GET",
        [1471] = "FULLAUTHORITYLIST_GET_RSP",
        [1472] = "USERS_GET",
        [1473] = "USERS_GET_RSP",
        [1474] = "GROUPS_GET",
        [1475] = "GROUPS_GET_RSP",
        [1476] = "ADDGROUP_REQ",
        [1477] = "ADDGROUP_RSP",
        [1478] = "MODIFYGROUP_REQ",
        [1479] = "MODIFYGROUP_RSP",
        [1480] = "DELETEGROUP_REQ",
        [1481] = "DELETEGROUP_RSP",
        [1482] = "ADDUSER_REQ",
        [1483] = "ADDUSER_RSP",
        [1484] = "MODIFYUSER_REQ",
        [1485] = "MODIFYUSER_RSP",
        [1486] = "DELETEUSER_REQ",
        [1487] = "DELETEUSER_RSP",
        [1488] = "MODIFYPASSWORD_REQ",
        [1489] = "MODIFYPASSWORD_RSP",
        [1500] = "GUARD_REQ",
        [1501] = "GUARD_RSP",
        [1502] = "UNGUARD_REQ",
        [1503] = "UNGUARD_RSP",
        [1504] = "ALARM_REQ",
        [1505] = "ALARM_RSP",
        [1506] = "NET_ALARM_REQ",
        [1507] = "NET_ALARM_REQ",
        [1508] = "ALARMCENTER_MSG_REQ",
        [1520] = "UPGRADE_REQ",
        [1521] = "UPGRADE_RSP",
        [1522] = "UPGRADE_DATA",
        [1523] = "UPGRADE_DATA_RSP",
        [1524] = "UPGRADE_PROGRESS",
        [1525] = "UPGRADE_INFO_REQ",
        [1526] = "UPGRADE_INFO_RSQ",
        [1530] = "IPSEARCH_REQ",
        [1531] = "IPSEARCH_RSP",
        [1532] = "IP_SET_REQ",
        [1533] = "IP_SET_RSP",
        [1540] = "CONFIG_IMPORT_REQ",
        [1541] = "CONFIG_IMPORT_RSP",
        [1542] = "CONFIG_EXPORT_REQ",
        [1543] = "CONFIG_EXPORT_RSP",
        [1544] = "LOG_EXPORT_REQ",
        [1545] = "LOG_EXPORT_RSP",
        [1550] = "NET_KEYBOARD_REQ",
        [1551] = "NET_KEYBOARD_RSP",
        [1560] = "NET_SNAP_REQ",
        [1561] = "NET_SNAP_RSP",
        [1562] = "SET_IFRAME_REQ",
        [1563] = "SET_IFRAME_RSP",
        [1570] = "RS232_READ_REQ",
        [1571] = "RS232_READ_RSP",
        [1572] = "RS232_WRITE_REQ",
        [1573] = "RS232_WRITE_RSP",
        [1574] = "RS485_READ_REQ",
        [1575] = "RS485_READ_RSP",
        [1576] = "RS485_WRITE_REQ",
        [1577] = "RS485_WRITE_RSP",
        [1578] = "TRANSPARENT_COMM_REQ",
        [1579] = "TRANSPARENT_COMM_RSP",
        [1580] = "RS485_TRANSPARENT_DATA_REQ",
        [1581] = "RS485_TRANSPARENT_DATA_RSP",
        [1582] = "RS232_TRANSPARENT_DATA_REQ",
        [1583] = "RS232_TRANSPARENT_DATA_RSP",
        [1590] = "SYNC_TIME_REQ",
        [1591] = "SYNC_TIME_RSP",
        [1600] = "PHOTO_GET_REQ",
        [1601] = "PHOTO_GET_RSP",
    }

    SOFIA = Proto("SOFIA", "Sofia")
    local f = SOFIA.fields

    f.protocol = ProtoField.uint8("sofia.protocol", "Protocol", base.HEX, {
        [0xff] = "sofia",
    })
    f.direction = ProtoField.uint8("sofia.direction", "Direction", base.DEC, {
        [1] = "incoming",
        [0] = "outgoing",
    })
    f.channel = ProtoField.uint8("sofia.channel", "Channel", base.DEC)
    f.reserved1 = ProtoField.uint8("sofia.reserved1", "Reserved #1", base.HEX)
    f.session_id = ProtoField.uint32("sofia.session_id", "Session ID", base.HEX)
    f.sequence = ProtoField.uint32("sofia.sequence", "Sequence", base.DEC)
    f.reserved2 = ProtoField.uint16("sofia.reserved2", "Reserved #2", base.HEX)
    f.command = ProtoField.uint16("sofia.command", "Command", base.DEC, commands)
    f.length = ProtoField.uint32("sofia.length", "Length", base.DEC)
    f.payload_json = ProtoField.string("sofia.payload", "JSON string")
    f.payload_raw = ProtoField.bytes("sofia.payload", "Raw data")

    function sofia_packet_length(buffer, pinfo, offset)
        local protocol = buffer(offset, 1):uint()
        if protocol ~= 0xff then
            return 20
        end

        local length = buffer(offset + 16, 4):le_uint()

        return length + 20
    end

    function sofia_dissect_packet(buffer, pinfo, root)
        local command = buffer(14, 2):le_uint()
        pinfo.cols.protocol = "Sofia (" .. commands[command] .. ")"

        local tree = root:add(SOFIA, buffer())
        local offset = 0

        local header = tree:add("Header", nil)
        header:add(f.protocol, buffer(0, 1))
        header:add(f.direction, buffer(1, 1))
        header:add(f.channel, buffer(2, 1))
        header:add(f.reserved1, buffer(3, 1))
        header:add_le(f.session_id, buffer(4, 4))
        header:add_le(f.sequence, buffer(8, 4))
        header:add_le(f.reserved2, buffer(12, 2))
        header:add_le(f.command, buffer(14, 2))
        header:add_le(f.length, buffer(16, 4))

        local payload = tree:add("Payload", nil)
        local length = buffer(16, 4):le_uint()
        local data = buffer(20, length)
        
        if data(0, 1):string() == '{' then
            payload:add(f.payload_json, data:string())
            Dissector.get("json"):call(data:tvb(), pinfo, payload)
        else
            payload:add(f.payload_raw, data)
        end
    end

    function SOFIA.dissector(buffer, pinfo, root)
        dissect_tcp_pdus(buffer, root, 20, sofia_packet_length, sofia_dissect_packet)
    end

    tcp_table = DissectorTable.get("tcp.port")
    tcp_table:add(34567, SOFIA)
end
