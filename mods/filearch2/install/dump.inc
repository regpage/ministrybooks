CREATE TABLE `filearch2_cats` (
  `id_cat` int(32) NOT NULL auto_increment,
  `title` tinytext,
  `descr` text,
  `pos` int(11) default NULL,
  PRIMARY KEY  (`id_cat`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#is_separator

CREATE TABLE `filearch2_items` (
  `id_item` int(32) NOT NULL auto_increment,
  `title` tinytext,
  `descr` text,
  `file` tinytext,
  `pos` int(11) default NULL,
  `date` datetime NOT NULL,
  `id_cat` int(11) default NULL,
  PRIMARY KEY  (`id_item`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#is_separator

CREATE TABLE `filearch2_stat` (
  `id_stat` int(32) NOT NULL auto_increment,
  `id_item` int(11) default NULL,
  `date` datetime default NULL,
  `id_cat` int(11) default NULL,
  `ip` tinytext NOT NULL,
  PRIMARY KEY  (`id_stat`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;