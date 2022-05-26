CREATE TABLE `url_and_sitetpl` (
  `id_item` int(32) NOT NULL auto_increment,
  `id_tpl` int(11) default NULL,
  `url` tinytext,
  `pos` int(11) default NULL,
  PRIMARY KEY  (`id_item`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 