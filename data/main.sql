CREATE TABLE `calibration` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`comment`	TEXT NOT NULL,
	`orange`	TEXT NOT NULL,
	`blue`	TEXT NOT NULL,
	`red`	TEXT NOT NULL,
	`pink`	TEXT NOT NULL,
	`purple`	TEXT NOT NULL,
	`green`	TEXT NOT NULL,
	`brown`	TEXT NOT NULL,
	`yellow`	TEXT NOT NULL,
	`rotation`	REAL NOT NULL,
	`cut`	TEXT NOT NULL,
	`data`	TEXT NOT NULL
);