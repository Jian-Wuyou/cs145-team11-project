-- Planetscale deployment
CREATE TABLE `readings` (
	`id` int NOT NULL AUTO_INCREMENT,
	`time` bigint unsigned NOT NULL,
	`temperature` float NOT NULL,
	`humidity` float NOT NULL,
	`heat_index` float NOT NULL,
	PRIMARY KEY (`id`)
) ENGINE InnoDB,
  CHARSET utf8mb4,
  COLLATE utf8mb4_0900_ai_ci;