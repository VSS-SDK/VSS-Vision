/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

CREATE TABLE `calibration` (
	`name`	TEXT NOT NULL,
	`orange`	TEXT NOT NULL,
	`blue`	TEXT NOT NULL,
	`yellow`	TEXT NOT NULL,
	`red`	TEXT NOT NULL,
	`pink`	TEXT NOT NULL,
	`purple`	TEXT NOT NULL,
	`green`	TEXT NOT NULL,
	`brown`	TEXT NOT NULL,
	`rotation`	REAL NOT NULL,
	`cut`	TEXT NOT NULL,
	`date`	TEXT NOT NULL
);

CREATE TABLE `configuration` (
	`name`	TEXT NOT NULL,
	`team1_main_color`	TEXT NOT NULL,
	`team1_secondary_color_1`	TEXT NOT NULL,
	`team1_secondary_color_2`	TEXT NOT NULL,
	`team1_secondary_color_3`	TEXT NOT NULL,
	`team2_main_color`	TEXT NOT NULL,
	`team2_secondary_color_1`	TEXT NOT NULL,
	`team2_secondary_color_2`	TEXT NOT NULL,
	`team2_secondary_color_3`	TEXT NOT NULL,
	`date`	TEXT NOT NULL
);
