SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema alert_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `alert_db` ;

-- -----------------------------------------------------
-- Schema alert_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `alert_db` DEFAULT CHARACTER SET utf8 ;
-- -----------------------------------------------------
-- Schema admin_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `admin_db` ;

-- -----------------------------------------------------
-- Schema admin_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `admin_db` ;
-- -----------------------------------------------------
-- Schema aog_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `aog_db` ;

-- -----------------------------------------------------
-- Schema aog_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `aog_db` ;
-- -----------------------------------------------------
-- Schema cmsp_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `cmsp_db` ;

-- -----------------------------------------------------
-- Schema cmsp_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `cmsp_db` ;
USE `alert_db` ;

-- -----------------------------------------------------
-- Table `alert_db`.`alert`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`alert` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`alert` (
  `alert_id` INT NOT NULL AUTO_INCREMENT,
  `sender_id` INT NOT NULL,
  `sent` DATETIME NOT NULL,
  `status` ENUM('ACTIVE', 'CANCELED', 'EXPIRED') NOT NULL,
  `type` ENUM('ACTUAL', 'EXERCISE', 'SYSTEM', 'TEST', 'DRAFT') NOT NULL,
  `source` VARCHAR(160) NULL,
  `scope` ENUM('PUBLIC', 'RESTRICTED', 'PRIVATE') NOT NULL,
  `restriction` VARCHAR(160) NULL,
  `addresses` VARCHAR(160) NULL,
  `code` BLOB NULL,
  `note` VARCHAR(160) NULL,
  `references` VARCHAR(160) NULL,
  `incidents` VARCHAR(160) NULL,
  PRIMARY KEY (`alert_id`),
  UNIQUE INDEX `alertID_UNIQUE` (`alert_id` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`info`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`info` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`info` (
  `alert_alert_id` INT NOT NULL,
  `language` VARCHAR(45) NULL,
  `type` VARCHAR(60) NOT NULL,
  `urgency` ENUM('IMMEDIATE', 'EXPECTED', 'FUTURE', 'PAST', 'UNKNOWN') NOT NULL,
  `severity` ENUM('EXTREME', 'SEVERE', 'MODERATE', 'MINOR', 'UNKNOWN') NOT NULL,
  `certainty` ENUM('OBSERVED', 'LIKELY', 'POSSIBLE', 'UNLIKELY', 'UNKNOWN') NOT NULL,
  `audience` VARCHAR(160) NULL,
  `event_code` BLOB NULL,
  `effective` DATETIME NULL,
  `onset` DATETIME NULL,
  `expires` DATETIME NULL,
  `sender_name` VARCHAR(160) NULL,
  `headline` VARCHAR(160) NULL,
  `description` VARCHAR(160) NULL,
  `instruction` VARCHAR(160) NULL,
  `web` VARCHAR(200) NULL,
  `contact` VARCHAR(160) NULL,
  `parameter` BLOB NULL,
  PRIMARY KEY (`alert_alert_id`),
  INDEX `fk_info_alert1_idx` (`alert_alert_id` ASC),
  CONSTRAINT `fk_info_alert1`
    FOREIGN KEY (`alert_alert_id`)
    REFERENCES `alert_db`.`alert` (`alert_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`category`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`category` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`category` (
  `alert_alert_id` INT NOT NULL,
  `category` ENUM('GEO', 'MET', 'SAFETY', 'SECURITY', 'RESCUE', 'FIRE', 'HEALTH', 'ENV', 'TRANSPORT', 'INFRA', 'CBRNE', 'OTHER') NOT NULL,
  PRIMARY KEY (`category`, `alert_alert_id`),
  INDEX `fk_category_alert1_idx` (`alert_alert_id` ASC),
  CONSTRAINT `fk_category_alert1`
    FOREIGN KEY (`alert_alert_id`)
    REFERENCES `alert_db`.`alert` (`alert_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`response_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`response_type` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`response_type` (
  `alert_alert_id` INT NOT NULL,
  `response_type` ENUM('SHELTER', 'EVACUATE', 'PREPARE', 'EXECUTE', 'AVOID', 'MONITOR', 'ALLCLEAR', 'NONE') NOT NULL,
  PRIMARY KEY (`response_type`, `alert_alert_id`),
  INDEX `fk_response_type_alert1_idx` (`alert_alert_id` ASC),
  CONSTRAINT `fk_response_type_alert1`
    FOREIGN KEY (`alert_alert_id`)
    REFERENCES `alert_db`.`alert` (`alert_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`resource`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`resource` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`resource` (
  `alert_alert_id` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `mime_type` VARCHAR(45) NOT NULL,
  `size` INT NOT NULL,
  `uri` BLOB NOT NULL,
  `deref_uri` BLOB NULL,
  `digest` BLOB NULL,
  PRIMARY KEY (`alert_alert_id`, `description`),
  INDEX `fk_resource_alert1_idx` (`alert_alert_id` ASC),
  CONSTRAINT `fk_resource_alert1`
    FOREIGN KEY (`alert_alert_id`)
    REFERENCES `alert_db`.`alert` (`alert_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
COMMENT = '			';


-- -----------------------------------------------------
-- Table `alert_db`.`area`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`area` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`area` (
  `alert_alert_id` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `polygon` BLOB NULL,
  `circle` BLOB NULL,
  `geocode` BLOB NULL,
  `altitude` INT NULL,
  `ceiling` INT NULL,
  PRIMARY KEY (`alert_alert_id`),
  CONSTRAINT `fk_area_alert1`
    FOREIGN KEY (`alert_alert_id`)
    REFERENCES `alert_db`.`alert` (`alert_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `admin_db` ;

-- -----------------------------------------------------
-- Table `admin_db`.`admin`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `admin_db`.`admin` ;

CREATE TABLE IF NOT EXISTS `admin_db`.`admin` (
  `user_id` INT NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(45) NOT NULL,
  `last_name` VARCHAR(45) NOT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `phone` VARCHAR(45) NULL,
  `address` VARCHAR(45) NULL,
  `country` VARCHAR(45) NULL,
  `state/region` VARCHAR(45) NULL,
  `zip` VARCHAR(10) NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE INDEX `userID_UNIQUE` (`user_id` ASC),
  UNIQUE INDEX `username_UNIQUE` (`username` ASC))
ENGINE = InnoDB
COMMENT = '				';

USE `aog_db` ;

-- -----------------------------------------------------
-- Table `aog_db`.`aog`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `aog_db`.`aog` ;

CREATE TABLE IF NOT EXISTS `aog_db`.`aog` (
  `aog_id` INT NOT NULL AUTO_INCREMENT,
  `agency` VARCHAR(45) NULL,
  `name` VARCHAR(45) NULL,
  `scope` ENUM('PUBLIC', 'RESTRICTED', 'PRIVATE') NULL,
  `ip` VARCHAR(45) NULL,
  PRIMARY KEY (`aog_id`),
  UNIQUE INDEX `groupID_UNIQUE` (`aog_id` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `aog_db`.`area`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `aog_db`.`area` ;

CREATE TABLE IF NOT EXISTS `aog_db`.`area` (
  `aog_aog_id` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `area` BLOB NULL,
  INDEX `fk_area_alert_originator_group_idx` (`aog_aog_id` ASC),
  PRIMARY KEY (`aog_aog_id`),
  CONSTRAINT `fk_area_alert_originator_group`
    FOREIGN KEY (`aog_aog_id`)
    REFERENCES `aog_db`.`aog` (`aog_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `aog_db`.`authentication`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `aog_db`.`authentication` ;

CREATE TABLE IF NOT EXISTS `aog_db`.`authentication` (
  `aog_aog_id` INT NOT NULL,
  `key` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`aog_aog_id`),
  CONSTRAINT `fk_authentication_alert_originator_group1`
    FOREIGN KEY (`aog_aog_id`)
    REFERENCES `aog_db`.`aog` (`aog_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `cmsp_db` ;

-- -----------------------------------------------------
-- Table `cmsp_db`.`table1`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cmsp_db`.`table1` ;

CREATE TABLE IF NOT EXISTS `cmsp_db`.`table1` (
  `cmsp_id` INT NOT NULL AUTO_INCREMENT,
  `ip` VARCHAR(12) NOT NULL,
  `port` INT NOT NULL,
  `cmsp` VARCHAR(45) NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`cmsp_id`),
  UNIQUE INDEX `cmsp_id_UNIQUE` (`cmsp_id` ASC),
  UNIQUE INDEX `ip_UNIQUE` (`ip` ASC))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
