-- MySQL dump 10.13  Distrib 5.6.17, for Win64 (x86_64)
--
-- Host: localhost    Database: bhouse
-- ------------------------------------------------------
-- Server version	5.6.21-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `scene`
--

DROP TABLE IF EXISTS `scene`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scene` (
  `s_id` char(36) NOT NULL,
  `b_id` char(36) NOT NULL,
  `name` varchar(80) NOT NULL,
  `modify_date` datetime NOT NULL,
  `designer` varchar(80) DEFAULT NULL,
  `desc` varchar(300) DEFAULT NULL,
  `download_times` bigint(10) unsigned NOT NULL,
  `views_count` int(3) NOT NULL,
  PRIMARY KEY (`s_id`),
  UNIQUE KEY `s_id_UNIQUE` (`s_id`),
  KEY `s_b_idx` (`b_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scene`
--

LOCK TABLES `scene` WRITE;
/*!40000 ALTER TABLE `scene` DISABLE KEYS */;
INSERT INTO `scene` VALUES ('36dc3fbc-3c2a-4e68-9bee-f4dea7deb425','503d5728-fc6c-52f1-a151-537778c296a5','暗黑卧室','2015-01-13 15:31:23','尹超','一个测试场景',0,2),('3d97adf8-fa20-4fd4-850d-bd00b57ac22a','503d5728-fc6c-52f1-a151-537778c296a5','卧室2','2015-01-13 15:40:04','xubo','测试场景2',866,2),('450a653f-3d3a-455f-9772-504a3237337a','503d5728-fc6c-52f1-a151-537778c296a5','书房','2015-01-13 15:19:05','舒弋','这是一个书房场景',0,2),('7a38b72e-63c3-459f-89c4-0633ab2540da','503d5728-fc6c-52f1-a151-537778c296a5','卧室','2015-01-13 15:25:19','储洁宇','这是一个棒棒哒卧室',0,1),('94a3b955-3d0d-496c-873b-8d47ea263b5d','503d5728-fc6c-52f1-a151-537778c296a5','美丽的书房','2015-01-13 15:29:43','杨成','这是一个美丽的书房',0,1),('a90cb734-83e7-498f-bc5b-1f4e84f074f3','503d5728-fc6c-52f1-a151-537778c296a5','厨房','2015-01-13 15:23:29','DALAB','厨房场景，啊！',16,1),('ba1af250-05ed-426a-b210-2471af24083f','503d5728-fc6c-52f1-a151-537778c296a5','厨房','2015-01-13 15:35:39','99','明亮的厨房场景',0,2),('e7d9c34b-f629-4798-ad3a-1c30206c85cb','503d5728-fc6c-52f1-a151-537778c296a5','向阳书房','2015-01-13 15:38:08','超哥','明亮的书房场景',0,1);
/*!40000 ALTER TABLE `scene` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tag`
--

DROP TABLE IF EXISTS `tag`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tag` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(80) NOT NULL,
  `desc` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tag`
--

LOCK TABLES `tag` WRITE;
/*!40000 ALTER TABLE `tag` DISABLE KEYS */;
INSERT INTO `tag` VALUES (1,'床上用品',''),(2,'柜子','啊，真实个好柜子呀好鬼子'),(3,'灯具',NULL),(4,'地面','可更换地面纹理的场景'),(5,'桌椅',''),(6,'窗帘','');
/*!40000 ALTER TABLE `tag` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tag_scene`
--

DROP TABLE IF EXISTS `tag_scene`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tag_scene` (
  `s_id` char(36) NOT NULL,
  `tag` int(11) NOT NULL,
  KEY `tag_tag_idx` (`tag`),
  KEY `id_s_idx` (`s_id`),
  CONSTRAINT `id_s` FOREIGN KEY (`s_id`) REFERENCES `scene` (`s_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `tag_tag_s` FOREIGN KEY (`tag`) REFERENCES `tag` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tag_scene`
--

LOCK TABLES `tag_scene` WRITE;
/*!40000 ALTER TABLE `tag_scene` DISABLE KEYS */;
INSERT INTO `tag_scene` VALUES ('450a653f-3d3a-455f-9772-504a3237337a',2),('450a653f-3d3a-455f-9772-504a3237337a',3),('450a653f-3d3a-455f-9772-504a3237337a',4),('450a653f-3d3a-455f-9772-504a3237337a',5),('a90cb734-83e7-498f-bc5b-1f4e84f074f3',2),('a90cb734-83e7-498f-bc5b-1f4e84f074f3',5),('7a38b72e-63c3-459f-89c4-0633ab2540da',1),('7a38b72e-63c3-459f-89c4-0633ab2540da',2),('7a38b72e-63c3-459f-89c4-0633ab2540da',4),('7a38b72e-63c3-459f-89c4-0633ab2540da',6),('94a3b955-3d0d-496c-873b-8d47ea263b5d',2),('94a3b955-3d0d-496c-873b-8d47ea263b5d',4),('94a3b955-3d0d-496c-873b-8d47ea263b5d',5),('36dc3fbc-3c2a-4e68-9bee-f4dea7deb425',2),('36dc3fbc-3c2a-4e68-9bee-f4dea7deb425',3),('ba1af250-05ed-426a-b210-2471af24083f',2),('ba1af250-05ed-426a-b210-2471af24083f',5),('e7d9c34b-f629-4798-ad3a-1c30206c85cb',2),('e7d9c34b-f629-4798-ad3a-1c30206c85cb',3),('e7d9c34b-f629-4798-ad3a-1c30206c85cb',5),('3d97adf8-fa20-4fd4-850d-bd00b57ac22a',2),('3d97adf8-fa20-4fd4-850d-bd00b57ac22a',3);
/*!40000 ALTER TABLE `tag_scene` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `u_id` char(36) NOT NULL,
  `name` varchar(80) NOT NULL,
  `email` varchar(80) NOT NULL,
  `password` char(40) NOT NULL,
  `salt` char(8) NOT NULL,
  `join_date` datetime NOT NULL,
  PRIMARY KEY (`u_id`),
  UNIQUE KEY `u_id_UNIQUE` (`u_id`),
  UNIQUE KEY `email_UNIQUE` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('00000000-0000-0000-0000-000000000000','test','test@meijia.com','2fd4e1c67a2d28fced849ee1bb76e7391b93eb12','00000000','2014-11-26 18:45:00'),('00000000-0000-0000-0000-000000000001','admin','admin@meijia.com','669ed24adebd6daa5f60e1e591d1633c54aae133','89515871','2014-11-26 18:45:00');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bhouse'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-01-13 15:44:02
