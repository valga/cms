#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>

#define SF_PWD_HASH_SIZE 8

#define SF_LOGIN_JSON "{\"EncryptType\":\"MD5\",\"LoginType\":\"Console\",\"PassWord\":\"%s\",\"UserName\":\"%s\"}"
#define SF_GENERIC_JSON "{\"Name\":\"%s\",\"SessionID\":\"%#x\"}"
#define SF_SYNC_TIME_JSON "{\"Name\":\"OPTimeSetting\",\"OPTimeSetting\":\"%04d-%02d-%02d %02d:%02d:%02d\",\"SessionID\":\"%#x\"}"
#define SF_SNAP_JSON "{\"Name\":\"OPSNAP\",\"OPSNAP\":{\"Channel\":0,\"CombinMode\":\"Extra1\"},\"SessionID\":\"%#x\"}"
#define SF_REBOOT_JSON "{\"Name\":\"OPMachine\",\"OPMachine\":{\"Action\":\"Reboot\"},\"SessionID\":\"%#x\"}"
#define SF_SET_CONFIG "{\"%s\":%s,\"Name\":\"%s\",\"SessionID\":\"%#x\"}"

typedef enum {
    SF_PROTO_SOFIA = 0xff
} SofiaProtocol;

typedef enum {
    SF_DIR_OUTGOING = 0x0,
    SF_DIR_INCOMING = 0x1
} SofiaPacketDirection;

typedef enum {
    SF_CMD_LOGIN_REQ = 1000,
    SF_CMD_LOGIN_RSP = 1001,
    SF_CMD_FORCELOGOUT_REQ = 1003,
    SF_CMD_FORCELOGOUT_RSP = 1004,
    SF_CMD_KEEPALIVE_REQ = 1006,
    SF_CMD_KEEPALIVE_RSP = 1007,
    SF_CMD_SYSINFO_REQ = 1020,
    SF_CMD_SYSINFO_RSP = 1021,
    SF_CMD_CONFIG_SET = 1040,
    SF_CMD_CONFIG_SET_RSP = 1041,
    SF_CMD_CONFIG_GET = 1042,
    SF_CMD_CONFIG_GET_RSP = 1043,
    SF_CMD_DEFAULT_CONFIG_GET = 1044,
    SF_CMD_DEFAULT_CONFIG_GET_RSP = 1045,
    SF_CMD_CONFIG_CHANNELTILE_SET = 1046,
    SF_CMD_CONFIG_CHANNELTILE_SET_RSP = 1047,
    SF_CMD_CONFIG_CHANNELTILE_GET = 1048,
    SF_CMD_CONFIG_CHANNELTILE_GET_RSP = 1049,
    SF_CMD_CONFIG_CHANNELTILE_DOT_SET = 1050,
    SF_CMD_CONFIG_CHANNELTILE_DOT_SET_RSP = 1051,
    SF_CMD_SYSTEM_DEBUG_REQ = 1052,
    SF_CMD_SYSTEM_DEBUG_RSP = 1053,
    SF_CMD_ABILITY_GET = 1360,
    SF_CMD_ABILITY_GET_RSP = 1361,
    SF_CMD_PTZ_REQ = 1400,
    SF_CMD_PTZ_RSP = 1401,
    SF_CMD_MONITOR_REQ = 1410,
    SF_CMD_MONITOR_RSP = 1411,
    SF_CMD_MONITOR_DATA = 1412,
    SF_CMD_MONITOR_CLAIM = 1413,
    SF_CMD_MONITOR_CLAIM_RSP = 1414,
    SF_CMD_PLAY_REQ = 1420,
    SF_CMD_PLAY_RSP = 1421,
    SF_CMD_PLAY_DATA = 1422,
    SF_CMD_PLAY_EOF = 1423,
    SF_CMD_PLAY_CLAIM = 1424,
    SF_CMD_PLAY_CLAIM_RSP = 1425,
    SF_CMD_DOWNLOAD_DATA = 1426,
    SF_CMD_TALK_REQ = 1430,
    SF_CMD_TALK_RSP = 1431,
    SF_CMD_TALK_CU_PU_DATA = 1432,
    SF_CMD_TALK_PU_CU_DATA = 1433,
    SF_CMD_TALK_CLAIM = 1434,
    SF_CMD_TALK_CLAIM_RSP = 1435,
    SF_CMD_FILESEARCH_REQ = 1440,
    SF_CMD_FILESEARCH_RSP = 1441,
    SF_CMD_LOGSEARCH_REQ = 1442,
    SF_CMD_LOGSEARCH_RSP = 1443,
    SF_CMD_FILESEARCH_BYTIME_REQ = 1444,
    SF_CMD_FILESEARCH_BYTIME_RSP = 1445,
    SF_CMD_SYSMANAGER_REQ = 1450,
    SF_CMD_SYSMANAGER_RSP = 1451,
    SF_CMD_TIMEQUERY_REQ = 1452,
    SF_CMD_TIMEQUERY_RSP = 1453,
    SF_CMD_DISKMANAGER_REQ = 1460,
    SF_CMD_DISKMANAGER_RSP = 1461,
    SF_CMD_FULLAUTHORITYLIST_GET = 1470,
    SF_CMD_FULLAUTHORITYLIST_GET_RSP = 1471,
    SF_CMD_USERS_GET = 1472,
    SF_CMD_USERS_GET_RSP = 1473,
    SF_CMD_GROUPS_GET = 1474,
    SF_CMD_GROUPS_GET_RSP = 1475,
    SF_CMD_ADDGROUP_REQ = 1476,
    SF_CMD_ADDGROUP_RSP = 1477,
    SF_CMD_MODIFYGROUP_REQ = 1478,
    SF_CMD_MODIFYGROUP_RSP = 1479,
    SF_CMD_DELETEGROUP_REQ = 1480,
    SF_CMD_DELETEGROUP_RSP = 1481,
    SF_CMD_ADDUSER_REQ = 1482,
    SF_CMD_ADDUSER_RSP = 1483,
    SF_CMD_MODIFYUSER_REQ = 1484,
    SF_CMD_MODIFYUSER_RSP = 1485,
    SF_CMD_DELETEUSER_REQ = 1486,
    SF_CMD_DELETEUSER_RSP = 1487,
    SF_CMD_MODIFYPASSWORD_REQ = 1488,
    SF_CMD_MODIFYPASSWORD_RSP = 1489,
    SF_CMD_GUARD_REQ = 1500,
    SF_CMD_GUARD_RSP = 1501,
    SF_CMD_UNGUARD_REQ = 1502,
    SF_CMD_UNGUARD_RSP = 1503,
    SF_CMD_ALARM_REQ = 1504,
    SF_CMD_ALARM_RSP = 1505,
    SF_CMD_NET_ALARM_REQ1 = 1506,
    SF_CMD_NET_ALARM_REQ2 = 1507,
    SF_CMD_ALARMCENTER_MSG_REQ = 1508,
    SF_CMD_UPGRADE_REQ = 1520,
    SF_CMD_UPGRADE_RSP = 1521,
    SF_CMD_UPGRADE_DATA = 1522,
    SF_CMD_UPGRADE_DATA_RSP = 1523,
    SF_CMD_UPGRADE_PROGRESS = 1524,
    SF_CMD_UPGRADE_INFO_REQ = 1525,
    SF_CMD_UPGRADE_INFO_RSQ = 1526,
    SF_CMD_IPSEARCH_REQ = 1530,
    SF_CMD_IPSEARCH_RSP = 1531,
    SF_CMD_IP_SET_REQ = 1532,
    SF_CMD_IP_SET_RSP = 1533,
    SF_CMD_CONFIG_IMPORT_REQ = 1540,
    SF_CMD_CONFIG_IMPORT_RSP = 1541,
    SF_CMD_CONFIG_EXPORT_REQ = 1542,
    SF_CMD_CONFIG_EXPORT_RSP = 1543,
    SF_CMD_LOG_EXPORT_REQ = 1544,
    SF_CMD_LOG_EXPORT_RSP = 1545,
    SF_CMD_NET_KEYBOARD_REQ = 1550,
    SF_CMD_NET_KEYBOARD_RSP = 1551,
    SF_CMD_NET_SNAP_REQ = 1560,
    SF_CMD_NET_SNAP_RSP = 1561,
    SF_CMD_SET_IFRAME_REQ = 1562,
    SF_CMD_SET_IFRAME_RSP = 1563,
    SF_CMD_RS232_READ_REQ = 1570,
    SF_CMD_RS232_READ_RSP = 1571,
    SF_CMD_RS232_WRITE_REQ = 1572,
    SF_CMD_RS232_WRITE_RSP = 1573,
    SF_CMD_RS485_READ_REQ = 1574,
    SF_CMD_RS485_READ_RSP = 1575,
    SF_CMD_RS485_WRITE_REQ = 1576,
    SF_CMD_RS485_WRITE_RSP = 1577,
    SF_CMD_TRANSPARENT_COMM_REQ = 1578,
    SF_CMD_TRANSPARENT_COMM_RSP = 1579,
    SF_CMD_RS485_TRANSPARENT_DATA_REQ = 1580,
    SF_CMD_RS485_TRANSPARENT_DATA_RSP = 1581,
    SF_CMD_RS232_TRANSPARENT_DATA_REQ = 1582,
    SF_CMD_RS232_TRANSPARENT_DATA_RSP = 1583,
    SF_CMD_SYNC_TIME_REQ = 1590,
    SF_CMD_SYNC_TIME_RSP = 1591,
    SF_CMD_PHOTO_GET_REQ = 1600,
    SF_CMD_PHOTO_GET_RSP = 1601,
} SofiaCommand;

typedef enum {
    SF_RET_OK = 100,
} SofiaReturnCode;

#pragma pack(push, 1)
typedef struct {
    uint8_t protocol;
    uint8_t direction;
    uint8_t channel;
    uint8_t reserved1;
    uint32_t session_id;
    uint32_t sequence_number;
    uint16_t reserved2;
    uint16_t command;
    uint32_t length;
} sf_header;

typedef struct {
    sf_header header;
    char payload[1];
} sf_message;
#pragma pack(pop)

void hash_password(const char *password, char *hash);

#endif
