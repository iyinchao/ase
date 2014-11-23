<?php

class DBConn
{
    const db_domain = 'localhost';
    const db_username = 'root';
    const db_password = '123456';
    const db_name = 'panocamp';
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01';
    const defaultUserEmail = 'default@panocamp.com';
    const defaultUserPassword = 'default';

    /*const db_domain = 'localhost';
    const db_username = 'iyinchao';
    const db_password = '920iYC!329';
    const db_name = 'iyinchao_panocamp';
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01';
    const defaultUserEmail = 'default@panocamp.com';
    const defaultUserPassword = 'default';*/

    public static function connect()
    {
        return new mysqli(self::db_domain, self::db_username, self::db_password, self::db_name);

    }
}

?>