<?php
include 'debug.php';

class DBConn
{
    const db_domain = 'localhost';
    const db_username = 'root';
    const db_password = '123456';
    const db_name = 'bhouse';

    public static function connect()
    {
        return new mysqli(self::db_domain, self::db_username, self::db_password, self::db_name);
    }

}

$conn = DBConn::connect();

?>