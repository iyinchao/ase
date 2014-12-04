CREATE DATABASE  IF NOT EXISTS `bhouse` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `bhouse`;
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
-- Table structure for table `brand`
--

DROP TABLE IF EXISTS `brand`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `brand` (
  `b_id` char(36) NOT NULL,
  `name` varchar(80) NOT NULL,
  `desc` varchar(300) DEFAULT NULL,
  `email` varchar(80) NOT NULL,
  `tel` varchar(20) DEFAULT NULL,
  `website` varchar(80) DEFAULT NULL,
  `modify_date` datetime DEFAULT NULL,
  PRIMARY KEY (`b_id`),
  UNIQUE KEY `b_id_UNIQUE` (`b_id`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  UNIQUE KEY `tel_UNIQUE` (`tel`),
  UNIQUE KEY `website_UNIQUE` (`website`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `brand`
--

LOCK TABLES `brand` WRITE;
/*!40000 ALTER TABLE `brand` DISABLE KEYS */;
INSERT INTO `brand` VALUES ('503d5728-fc6c-52f1-a151-537778c296a5','MeijiaTest','This is a test brand','test@meijia.com','12345678910','www.meijia.com','2014-12-03 10:42:08'),('7918c182-6581-42cb-8805-0508e15aa0b5','SJTU','This is a test brand','meijia@sjtu.edu.cn',NULL,NULL,'2014-12-04 21:50:27');
/*!40000 ALTER TABLE `brand` ENABLE KEYS */;
UNLOCK TABLES;

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
  `download_times` bigint(20) unsigned zerofill NOT NULL,
  `views_count` int(3) NOT NULL,
  PRIMARY KEY (`s_id`),
  UNIQUE KEY `s_id_UNIQUE` (`s_id`),
  KEY `s_b_idx` (`b_id`),
  CONSTRAINT `s_b` FOREIGN KEY (`b_id`) REFERENCES `brand` (`b_id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scene`
--

LOCK TABLES `scene` WRITE;
/*!40000 ALTER TABLE `scene` DISABLE KEYS */;
INSERT INTO `scene` VALUES ('0b7587a9-940c-4965-9cbc-45c3a1380ae5','503d5728-fc6c-52f1-a151-537778c296a5','Test2','2014-12-04 21:48:47','ShuYi','This the test scene',00000000000000000000,1),('1630b189-4383-4a1b-a955-cfeb228ed5bc','503d5728-fc6c-52f1-a151-537778c296a5','Test3','2014-12-04 21:48:47','YangCheng','This the test scene',00000000000000000000,1),('180d2d0d-730c-45aa-bd3b-9493cd29985f','7918c182-6581-42cb-8805-0508e15aa0b5','Test4','2014-12-04 21:48:46','YinChao','This the test scene',00000000000000000000,1),('276ab768-ca9e-44a7-969c-be7bafcd6bb9','7918c182-6581-42cb-8805-0508e15aa0b5','Test8','2014-12-04 21:48:42','ChaoGe','This the test scene',00000000000000000000,1),('51ff6575-53fa-4ad6-be5b-426de31b500c','7918c182-6581-42cb-8805-0508e15aa0b5','Test6','2014-12-04 21:48:44','LaoYang','This the test scene',00000000000000000000,1),('6d05d6ba-4ca2-523c-8a15-adbbfe4f2265','503d5728-fc6c-52f1-a151-537778c296a5','Test','2014-12-03 10:59:01','Charles','This the test scene',00000000000000000009,1),('bbfa1cf3-cb0a-4407-998b-9494bcd35036','7918c182-6581-42cb-8805-0508e15aa0b5','Test5','2014-12-04 21:48:45','ChuJieyu','This the test scene',00000000000000000000,1),('d6dd5a71-5101-415b-9cc8-cb016e17e10f','7918c182-6581-42cb-8805-0508e15aa0b5','Test7','2014-12-04 21:48:43','PengYe','This the test scene',00000000000000000000,1);
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
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tag`
--

LOCK TABLES `tag` WRITE;
/*!40000 ALTER TABLE `tag` DISABLE KEYS */;
INSERT INTO `tag` VALUES (1,'Child','Suitable for children'),(2,'Young couple',NULL),(3,'SOHO',NULL),(4,'Bright',NULL);
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
INSERT INTO `tag_scene` VALUES ('0b7587a9-940c-4965-9cbc-45c3a1380ae5',1),('1630b189-4383-4a1b-a955-cfeb228ed5bc',2),('180d2d0d-730c-45aa-bd3b-9493cd29985f',3),('276ab768-ca9e-44a7-969c-be7bafcd6bb9',4),('51ff6575-53fa-4ad6-be5b-426de31b500c',4),('6d05d6ba-4ca2-523c-8a15-adbbfe4f2265',3),('bbfa1cf3-cb0a-4407-998b-9494bcd35036',2),('d6dd5a71-5101-415b-9cc8-cb016e17e10f',1),('6d05d6ba-4ca2-523c-8a15-adbbfe4f2265',2),('6d05d6ba-4ca2-523c-8a15-adbbfe4f2265',4),('0b7587a9-940c-4965-9cbc-45c3a1380ae5',3),('0b7587a9-940c-4965-9cbc-45c3a1380ae5',4);
/*!40000 ALTER TABLE `tag_scene` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tag_uscene`
--

DROP TABLE IF EXISTS `tag_uscene`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tag_uscene` (
  `us_id` char(36) NOT NULL,
  `tag` int(11) NOT NULL,
  KEY `id_us_idx` (`us_id`),
  KEY `tag_tag_idx` (`tag`),
  CONSTRAINT `id_us` FOREIGN KEY (`us_id`) REFERENCES `user_scene` (`us_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `tag_tag_u` FOREIGN KEY (`tag`) REFERENCES `tag` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tag_uscene`
--

LOCK TABLES `tag_uscene` WRITE;
/*!40000 ALTER TABLE `tag_uscene` DISABLE KEYS */;
/*!40000 ALTER TABLE `tag_uscene` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `u_id` char(36) NOT NULL,
  `password` char(40) NOT NULL,
  `email` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
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
INSERT INTO `user` VALUES ('00000000-0000-0000-0000-000000000000','2fd4e1c67a2d28fced849ee1bb76e7391b93eb12','test@meijia.com','test','2014-11-26 18:45:00');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_scene`
--

DROP TABLE IF EXISTS `user_scene`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_scene` (
  `us_id` char(36) NOT NULL,
  `u_id` char(36) NOT NULL,
  `s_id` char(36) NOT NULL,
  `name` varchar(80) NOT NULL,
  `modify_date` datetime NOT NULL,
  PRIMARY KEY (`us_id`),
  UNIQUE KEY `us_id_UNIQUE` (`us_id`),
  KEY `us_u_idx` (`u_id`),
  KEY `us_s_idx` (`s_id`),
  CONSTRAINT `us_s` FOREIGN KEY (`s_id`) REFERENCES `scene` (`s_id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `us_u` FOREIGN KEY (`u_id`) REFERENCES `user` (`u_id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_scene`
--

LOCK TABLES `user_scene` WRITE;
/*!40000 ALTER TABLE `user_scene` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_scene` ENABLE KEYS */;
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

-- Dump completed on 2014-12-04 22:29:38
