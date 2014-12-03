<?php
include_once 'debug.php';

/**
 * Class DBConn
 */
class DBConn
{
    const db_domain = 'localhost';
    const db_username = 'root';
    const db_password = '123456';
    const db_name = 'bhouse';

    /**
     * @return mysqli
     */
    public static function connect(){
        @$conn = new mysqli(self::db_domain, self::db_username, self::db_password, self::db_name);
        if($conn->connect_errno) throw new Exception($conn->connect_error);
        return $conn;
    }

}
?>