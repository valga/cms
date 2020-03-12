# cms

A tool to control Sofia-powered chinese IP-cameras.

## Usage

```
cms [USERNAME[:PASSWORD]@]IP[:PORT] COMMAND --ARGS...
```

Default values:


| Parameter | Value     |
|-----------|-----------|
| USERNAME  | admin     |
| PASSWORD  | *empty*   |
| PORT      | 34567     |

## Available commands

### getconfig

Returns JSON config from the device.

```
cms 192.168.1.10 getconfig --key "Camera.ParamEx[0].BroadTrends.AutoGain"
```

### setconfig

Updates JSON config on the device.

```
cms 192.168.1.10 setconfig --key "Camera.ParamEx[0].BroadTrends.AutoGain" --value "1"
```

### gettime

Returns a datetime from the device.

```
cms 192.168.1.10 gettime
```

### synctime

Updates device datetime to the current one.

```
cms 192.168.1.10 gettime
```

### snap

Creates a JPEG snapshot.

```
cms 192.168.1.10 snap > snap.jpg
```

### reboot

Reboots the device.

```
cms 192.168.1.10 reboot
```

## Credits

[667bdrm](https://github.com/667bdrm/sofiactl) for password hashing algo and stuff.
