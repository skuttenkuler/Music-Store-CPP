SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";


-- MUSIC STORE DATABASE --
CREATE DATABASE music_store;
USE music_store;
-- TABLE FOR MERCHANDISE --

CREATE TABLE `music_store_table` (
	`id` INT NOT NULL AUTO_INCREMENT,
	`artist` varchar(100) NOT NULL DEFAULT '0',
	`album` varchar(100) NOT NULL DEFAULT '0',
	`genre` varchar(100) DEFAULT '0',
	`price` varchar(100) NOT NULL DEFAULT '0',
	`quantity` varchar(100) NOT NULL DEFAULT '0',
    PRIMARY KEY(id)
	);

INSERT INTO `music_store_inventory` (`id`,`artist`,`album`,`genre`,`price`,`quantity`) VALUES
(1, 'The Beatles', 'White Album', 'rock', '25', '50'),
(2, 'Opeth', 'Watershed', 'metal', '25', '15'),
(3, 'Steely Dan', 'The Royal Scam', 'rock', '25', '50'),
(4, 'Miles Davis', 'Bitches Brew', 'jazz', '35', '2'),
(5, 'E-40', 'The Ball Street Journal', 'rap', '25', '15'),
(6, 'Deafheaven', 'New Burmuda', 'metal', '20', '2'),
(7, 'Architects', 'For Those That Wish To Exist', 'metal', '30', '50'),
(8, 'The Band', 'The Band', 'rock', '25', '50'),
(9, 'Sturgill Simpson', 'High Top Mountain', 'country', '20', '1'),
(10, 'The Beatles', 'Sgt. Peppers Lonely Hearts Club Band', 'rock', '25', '10');