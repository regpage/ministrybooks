CREATE TABLE `forms` (
  `id_form` int(32) NOT NULL auto_increment,
  `title` tinytext,
  `email_from` tinytext,
  `encoding` tinytext,
  `subject` tinytext,
  `sended_den` text NOT NULL,
  `sended_mess` text NOT NULL,
  `pos` int(11) NOT NULL,
  PRIMARY KEY  (`id_form`)
) ENGINE=MyIsam DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

#is_separator

INSERT INTO `forms` (`id_form`, `title`, `email_from`, `encoding`, `subject`, `sended_den`, `sended_mess`, `pos`) VALUES
(1, 'Programmer Resume', 'ortus.yoursite.com', 'utf8', 'Programmer Resume', '<p>Your have already sent a message</p>', '<p>Your message is succesfully sent.</p>', 1),
(2, 'Contact form', 'ortus@yoursite.com', 'utf8', 'your contact form is submitted', '<p>You have already sent a message..</p>', '<p>Your message is succesfully sent.</p>', 2);

#is_separator

CREATE TABLE `forms_emails_to` (
  `id_email` int(32) NOT NULL auto_increment,
  `email` tinytext,
  `id_form` int(11) default NULL,
  PRIMARY KEY  (`id_email`)
) ENGINE=MyIsam DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

#is_separator

INSERT INTO `forms_emails_to` (`id_email`, `email`, `id_form`) VALUES
(1, 'antf@inbox.ru', 1);

#is_separator

CREATE TABLE `forms_fields` (
  `id_field` int(32) NOT NULL auto_increment,
  `field_name` tinytext,
  `type` tinytext,
  `caption` tinytext,
  `oblig` enum('yes','no') default NULL,
  `params` mediumtext,
  `pos` int(11) default NULL,
  `page` int(11) NOT NULL,
  `id_form` int(11) default NULL,
  PRIMARY KEY  (`id_field`)
) ENGINE=MyIsam DEFAULT CHARSET=utf8 AUTO_INCREMENT=48 ;

#is_separator

INSERT INTO `forms_fields` (`id_field`, `field_name`, `type`, `caption`, `oblig`, `params`, `pos`, `page`, `id_form`) VALUES
(19, '', 'groupe_title', 'Page 1', 'no', '', 1, 1, 1),
(20, 'your_name', 'text', 'Name', 'yes', 'a:1:{s:13:"default_value";s:0:"";}', 2, 1, 1),
(21, 'address', 'text', 'Address', 'yes', 'a:1:{s:13:"default_value";s:41:"1234, West 67 Street, Carlisle, MA 01741,";}', 3, 1, 1),
(22, 'tel', 'text', 'Tel', 'yes', 'a:1:{s:13:"default_value";s:0:"";}', 4, 1, 1),
(23, 'email', 'text', 'E-mail', 'no', 'a:1:{s:13:"default_value";s:0:"";}', 5, 1, 1),
(24, '', 'groupe_title', 'Page 2', 'no', '', 1, 2, 1),
(25, 'relevant_experience', 'textarea', 'Relevant experience', 'no', 'a:2:{s:8:"num_rows";i:6;s:13:"default_value";s:352:"Possesses over nine (9) years of experience in various areas of Systems Analysis and Software Development. Experience includes a concentration in HP3000 mainframe based programming. Supports company web based applications using web authoring PC based software. A leader with five years as System Analyst/Lead Developer for a Software Development group.";}', 2, 2, 1),
(26, '', 'groupe_title', 'Your skills', 'no', '', 3, 2, 1),
(27, 'ci', 'checkbox', 'C', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 4, 2, 1),
(28, 'cplusplus', 'checkbox', 'C++', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 5, 2, 1),
(29, 'pascal', 'checkbox', 'Pascal (Object Pascal)', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 6, 2, 1),
(30, 'html', 'checkbox', 'HTML', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 7, 2, 1),
(31, 'css', 'checkbox', 'CSS', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 8, 2, 1),
(32, 'javascript', 'checkbox', 'Java Script', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 9, 2, 1),
(33, 'xml', 'checkbox', 'XML', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 10, 2, 1),
(34, 'php', 'checkbox', 'PHP', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 11, 2, 1),
(35, 'perl', 'checkbox', 'PERL', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 12, 2, 1),
(36, 'parser', 'checkbox', 'PARSER', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 13, 2, 1),
(37, 'asp', 'checkbox', 'ASP', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 14, 2, 1),
(38, 'mysql', 'checkbox', 'MySQL', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 15, 2, 1),
(39, 'postgresql', 'checkbox', 'PosgreSQL', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 16, 2, 1),
(40, 'mssql', 'checkbox', 'MSSQL', 'no', 'a:3:{s:7:"yes_rep";s:2:"да";s:6:"no_rep";s:3:"нет";s:7:"checked";s:2:"no";}', 17, 2, 1),
(41, 'other_skills', 'textarea', 'Other skills', 'no', 'a:2:{s:8:"num_rows";i:6;s:13:"default_value";s:0:"";}', 18, 2, 1),
(42, '', 'groupe_title', 'Page 3', 'no', '', 1, 3, 1),
(43, 'education', 'textarea', 'Education', 'yes', 'a:2:{s:8:"num_rows";i:6;s:13:"default_value";s:80:"BA - Buisness Community College, Clackamas\r\nPortland Community College, Portland";}', 2, 3, 1),
(44, 'experience', 'textarea', 'Experience highlights', 'yes', 'a:2:{s:8:"num_rows";i:12;s:13:"default_value";s:534:"Programmer/Analyst New Mexico Educational Assistance Foundation (July, 1991 - February, 1994)\r\n\r\n    * Solved end user problems in a production support capacity.\r\n    * Wrote and analyzed software programs in Cobol and Speedware.\r\n    * Maintained an existing mainframe production environment. \r\n\r\nComputer Lab Consultant University of New Mexico (October, 1990 - May, 1991)\r\n\r\n    * Managed a functioning computer lab including maintenance of hardware and software.\r\n    * Assisted student users with hardware and general questions. ";}', 3, 3, 1),
(45, 'email', 'text', 'Your email', 'yes', 'a:1:{s:13:"default_value";s:0:"";}', 1, 1, 2),
(46, 'subject', 'text', 'Subject', 'yes', 'a:1:{s:13:"default_value";s:0:"";}', 2, 1, 2),
(47, 'post', 'textarea', 'Message', 'yes', 'a:2:{s:8:"num_rows";i:8;s:13:"default_value";s:0:"";}', 3, 1, 2);

#is_separator

CREATE TABLE `forms_messages` (
  `id_mess` int(32) NOT NULL auto_increment,
  `message` mediumtext,
  `date` datetime default NULL,
  `id_form` int(11) default NULL,
  PRIMARY KEY  (`id_mess`)
) ENGINE=MyIsam DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

#is_separator

INSERT INTO `forms_messages` (`id_mess`, `message`, `date`, `id_form`) VALUES
(1, 'Programmer Resume \r\n\r\nFrom http://localhost/ortus/\r\nDate 17 Nov 2007 0:20:17\r\n\r\nName: Richard Anderson,,\r\nAddress: 1234, West 67 Street, Carlisle, MA 01741,\r\nTel: (123)-456 7890.\r\nE-mail: поле не заполнено\r\nSite: {site}\r\n\r\nRELEVANT EXPERIENCE\r\n\r\nPossesses over nine (9) years of experience in various areas of Systems Analysis and Software Development. Experience includes a concentration in HP3000 mainframe based programming. Supports company web based applications using web authoring PC based software. A leader with five years as System Analyst/Lead Developer for a Software Development group.\r\n\r\nSKILLS\r\n\r\nC - нет \r\nC++ - да\r\nPascal - да\r\nHTML - да\r\nCSS - да\r\nJava Script - нет\r\nXML - нет\r\nPHP - да\r\nPERL - нет\r\nPARSER - нет\r\nASP - нет\r\nMySQL - да\r\nPostreSQL - да\r\nMsSQL - да\r\n\r\nEDUCATION\r\nBA - Buisness Community College, Clackamas\r\nPortland Community College, Portland\r\n\r\nEXPERIENCE HIGHLIGHTS \r\nProgrammer/Analyst New Mexico Educational Assistance Foundation (July, 1991 - February, 1994)\r\n\r\n    * Solved end user problems in a production support capacity.\r\n    * Wrote and analyzed software programs in Cobol and Speedware.\r\n    * Maintained an existing mainframe production environment. \r\n\r\nComputer Lab Consultant University of New Mexico (October, 1990 - May, 1991)\r\n\r\n    * Managed a functioning computer lab including maintenance of hardware and software.\r\n    * Assisted student users with hardware and general questions. ', '2007-11-17 00:20:17', 1),
(2, 'Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.\r\n', '2007-11-17 00:09:44', 2);

#is_separator

CREATE TABLE `forms_messtpl` (
  `id_tpl` int(32) NOT NULL auto_increment,
  `tpl` mediumtext,
  `id_form` int(11) default NULL,
  PRIMARY KEY  (`id_tpl`)
) ENGINE=MyIsam DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

#is_separator

INSERT INTO `forms_messtpl` (`id_tpl`, `tpl`, `id_form`) VALUES
(1, 'Programmer Resume \r\n\r\nFrom {your_site}\r\nDate {date}\r\n\r\nName: {your_name},\r\nAddress: {address}\r\nTel: {tel}\r\nE-mail: {email}\r\n\r\nRELEVANT EXPERIENCE\r\n\r\n{relevant_experience}\r\n\r\nSKILLS\r\n\r\nC - {ci} \r\nC++ - {cplusplus}\r\nPascal - {pascal}\r\nHTML - {html}\r\nCSS - {css}\r\nJava Script - {javascript}\r\nXML - {xml}\r\nPHP - {php}\r\nPERL - {perl}\r\nPARSER - {parser}\r\nASP - {asp}\r\nMySQL - {mysql}\r\nPostreSQL - {postgresql}\r\nMsSQL - {mssql}\r\n\r\nEDUCATION\r\n{education}\r\n\r\nEXPERIENCE HIGHLIGHTS \r\n{experience}', 1),
(2, 'From: {your_site}\r\nDate: {date}\r\n\r\nSubject: \r\n{subject} \r\n\r\nE-mail from: \r\n{email} \r\n\r\nMESSAGE\r\n\r\n{post}', 2);
