-- MySQL Script generated by MySQL Workbench
-- Fri Nov 23 19:14:29 2018
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

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
-- Schema cadg_admin_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `cadg_admin_db` ;

-- -----------------------------------------------------
-- Schema cadg_admin_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `cadg_admin_db` ;
-- -----------------------------------------------------
-- Schema alert_originator_group_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `alert_originator_group_db` ;

-- -----------------------------------------------------
-- Schema alert_originator_group_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `alert_originator_group_db` ;
USE `alert_db` ;

-- -----------------------------------------------------
-- Table `alert_db`.`alert`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`alert` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`alert` (
  `alertID` INT NOT NULL AUTO_INCREMENT,
  `senderID` INT NOT NULL,
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
  PRIMARY KEY (`alertID`),
  UNIQUE INDEX `alertID_UNIQUE` (`alertID` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`info`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`info` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`info` (
  `alert_alertID` INT NOT NULL,
  `language` VARCHAR(45) NULL,
  `type` VARCHAR(60) NOT NULL,
  `urgency` ENUM('IMMEDIATE', 'EXPECTED', 'FUTURE', 'PAST', 'UNKNOWN') NOT NULL,
  `severity` ENUM('EXTREME', 'SEVERE', 'MODERATE', 'MINOR', 'UNKNOWN') NOT NULL,
  `certainty` ENUM('OBSERVED', 'LIKELY', 'POSSIBLE', 'UNLIKELY', 'UNKNOWN') NOT NULL,
  `audience` VARCHAR(160) NULL,
  `eventCode` BLOB NULL,
  `effective` DATETIME NULL,
  `onset` DATETIME NULL,
  `expires` DATETIME NULL,
  `senderName` VARCHAR(160) NULL,
  `headline` VARCHAR(160) NULL,
  `description` VARCHAR(160) NULL,
  `instruction` VARCHAR(160) NULL,
  `web` VARCHAR(200) NULL,
  `contact` VARCHAR(160) NULL,
  `parameter` BLOB NULL,
  PRIMARY KEY (`alert_alertID`),
  INDEX `fk_info_alert1_idx` (`alert_alertID` ASC),
  CONSTRAINT `fk_info_alert1`
    FOREIGN KEY (`alert_alertID`)
    REFERENCES `alert_db`.`alert` (`alertID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`category`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`category` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`category` (
  `alert_alertID` INT NOT NULL,
  `category` ENUM('GEO', 'MET', 'SAFETY', 'SECURITY', 'RESCUE', 'FIRE', 'HEALTH', 'ENV', 'TRANSPORT', 'INFRA', 'CBRNE', 'OTHER') NOT NULL,
  PRIMARY KEY (`category`, `alert_alertID`),
  INDEX `fk_category_alert1_idx` (`alert_alertID` ASC),
  CONSTRAINT `fk_category_alert1`
    FOREIGN KEY (`alert_alertID`)
    REFERENCES `alert_db`.`alert` (`alertID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`response_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`response_type` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`response_type` (
  `alert_alertID` INT NOT NULL,
  `response_type` ENUM('SHELTER', 'EVACUATE', 'PREPARE', 'EXECUTE', 'AVOID', 'MONITOR', 'ALLCLEAR', 'NONE') NOT NULL,
  PRIMARY KEY (`response_type`, `alert_alertID`),
  INDEX `fk_response_type_alert1_idx` (`alert_alertID` ASC),
  CONSTRAINT `fk_response_type_alert1`
    FOREIGN KEY (`alert_alertID`)
    REFERENCES `alert_db`.`alert` (`alertID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_db`.`resource`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`resource` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`resource` (
  `alert_alertID` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `mimeType` VARCHAR(45) NOT NULL,
  `size` INT NOT NULL,
  `uri` BLOB NOT NULL,
  `derefUri` BLOB NULL,
  `digest` BLOB NULL,
  PRIMARY KEY (`alert_alertID`, `description`),
  INDEX `fk_resource_alert1_idx` (`alert_alertID` ASC),
  CONSTRAINT `fk_resource_alert1`
    FOREIGN KEY (`alert_alertID`)
    REFERENCES `alert_db`.`alert` (`alertID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
COMMENT = '			';


-- -----------------------------------------------------
-- Table `alert_db`.`area`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_db`.`area` ;

CREATE TABLE IF NOT EXISTS `alert_db`.`area` (
  `alert_alertID` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `polygon` BLOB NULL,
  `circle` BLOB NULL,
  `geocode` BLOB NULL,
  `altitude` INT NULL,
  `ceiling` INT NULL,
  PRIMARY KEY (`alert_alertID`),
  CONSTRAINT `fk_area_alert1`
    FOREIGN KEY (`alert_alertID`)
    REFERENCES `alert_db`.`alert` (`alertID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `cadg_admin_db` ;

-- -----------------------------------------------------
-- Table `cadg_admin_db`.`admin`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cadg_admin_db`.`admin` ;

CREATE TABLE IF NOT EXISTS `cadg_admin_db`.`admin` (
  `userID` INT NOT NULL AUTO_INCREMENT,
  `firstName` VARCHAR(45) NOT NULL,
  `lastName` VARCHAR(45) NOT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE INDEX `userID_UNIQUE` (`userID` ASC),
  UNIQUE INDEX `username_UNIQUE` (`username` ASC))
ENGINE = InnoDB;

USE `alert_originator_group_db` ;

-- -----------------------------------------------------
-- Table `alert_originator_group_db`.`alert_originator_group`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_originator_group_db`.`alert_originator_group` ;

CREATE TABLE IF NOT EXISTS `alert_originator_group_db`.`alert_originator_group` (
  `groupID` INT NOT NULL AUTO_INCREMENT,
  `scope` ENUM('PUBLIC', 'RESTRICTED', 'PRIVATE') NULL,
  PRIMARY KEY (`groupID`),
  UNIQUE INDEX `groupID_UNIQUE` (`groupID` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_originator_group_db`.`area`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_originator_group_db`.`area` ;

CREATE TABLE IF NOT EXISTS `alert_originator_group_db`.`area` (
  `alert_originator_group_groupID` INT NOT NULL,
  `description` VARCHAR(160) NOT NULL,
  `area` BLOB NULL,
  INDEX `fk_area_alert_originator_group_idx` (`alert_originator_group_groupID` ASC),
  PRIMARY KEY (`alert_originator_group_groupID`),
  CONSTRAINT `fk_area_alert_originator_group`
    FOREIGN KEY (`alert_originator_group_groupID`)
    REFERENCES `alert_originator_group_db`.`alert_originator_group` (`groupID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `alert_originator_group_db`.`authentication`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `alert_originator_group_db`.`authentication` ;

CREATE TABLE IF NOT EXISTS `alert_originator_group_db`.`authentication` (
  `alert_originator_group_groupID` INT NOT NULL,
  `key` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`alert_originator_group_groupID`),
  CONSTRAINT `fk_authentication_alert_originator_group1`
    FOREIGN KEY (`alert_originator_group_groupID`)
    REFERENCES `alert_originator_group_db`.`alert_originator_group` (`groupID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
