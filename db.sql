
CREATE TABLE `items` (
  `id` int(11) NOT NULL,
  `name` text NOT NULL,
  `quantity` int(11) NOT NULL DEFAULT '0',
  `avgprice` int(11) NOT NULL DEFAULT '0',
  `date` date NOT NULL 


CREATE TABLE `sold` (
  `type` int(11) NOT NULL,
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `quantity` int(11) NOT NULL,
  `sellprice` int(11) NOT NULL DEFAULT '0',
  `date` date NOT NULL 
) ;





ALTER TABLE `items`
  ADD PRIMARY KEY (`id`);


ALTER TABLE `sold`
  ADD PRIMARY KEY (`id`);


ALTER TABLE `items`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=0;

ALTER TABLE `sold`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=0;

