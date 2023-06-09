-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: cs145_heathelm
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `readings`
--

DROP TABLE IF EXISTS `readings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `readings` (
  `id` tinyint unsigned NOT NULL,
  `time` int unsigned NOT NULL,
  `temperature` float unsigned NOT NULL,
  `humidity` float unsigned NOT NULL,
  `heat index` float unsigned NOT NULL,
  PRIMARY KEY (`id`,`time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `readings`
--

LOCK TABLES `readings` WRITE;
/*!40000 ALTER TABLE `readings` DISABLE KEYS */;
INSERT INTO `readings` VALUES (1,1684824494,49,49,21),(1,1684824496,38,31,24),(1,1684824498,48,26,26),(1,1684824500,29,45,33),(1,1684824502,43,36,31),(1,1684824504,21,40,49),(1,1684824506,47,25,26),(1,1684824508,28,48,45),(1,1684824510,26,25,41),(1,1684824512,49,20,20),(1,1684824514,47,27,27),(1,1684824516,44,28,45),(1,1684824518,34,49,26),(1,1684824520,24,33,22),(1,1684824523,42,26,30),(1,1684824525,45,25,20),(1,1684824527,29,45,40),(1,1684824529,21,39,33),(1,1684824531,44,33,39),(1,1684824533,42,35,29),(1,1684824535,48,26,42),(1,1684824537,45,23,27),(1,1684824539,21,22,26),(1,1684824541,46,22,41),(1,1684824543,49,29,21),(1,1684824545,28,26,43),(1,1684824547,32,36,23),(1,1684824549,21,29,42),(1,1684824552,33,44,29),(1,1684824554,42,44,37),(1,1684824556,48,42,37),(1,1684824558,21,49,39),(1,1684824560,29,49,48),(1,1684824562,37,30,24),(1,1684824564,32,27,39),(1,1684824566,22,42,48),(1,1684824568,27,48,44),(1,1684824570,42,23,49),(1,1684824572,41,31,31),(1,1684824574,26,32,36),(1,1684824576,35,34,23),(1,1684824578,25,42,41),(1,1684824580,38,41,25),(1,1684824583,45,23,39),(1,1684824585,33,23,46),(1,1684824587,32,47,29),(1,1684824589,36,31,44),(1,1684824591,48,25,30),(1,1684824593,36,21,49),(1,1684824595,24,30,25),(1,1684824597,34,34,25),(1,1684824599,37,35,42),(1,1684824601,20,49,43),(1,1684824603,44,44,29),(1,1684824605,44,21,47),(1,1684824607,38,26,31),(1,1684824609,38,37,24),(1,1684824611,38,43,36),(1,1684824614,40,37,31),(1,1684824616,30,30,30),(1,1684824618,30,30,30),(1,1684824620,30,100,30),(1,1684824622,30,100,30),(1,1684824624,30,100,30),(1,1684824627,30,13,30),(2,1,12,12,12);
/*!40000 ALTER TABLE `readings` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-05-24 22:45:16
