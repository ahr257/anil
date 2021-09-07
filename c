Select A.FINANCIAL_YEAR,B.DISTRICT_CODE,B.DISTRICT_NAME,B.MANDAL_CODE,B.MANDAL_NAME,
B.SECRETARIAT_CODE,B.SECRETARIAT_NAME,B.RURAL_URBAN_FLAG,B.HOUSEHOLD_ID,to_char(A.UID_NUM) AS UID_NUM,
'YSR PENSIONS' AS SCHEME_NAME,A.AMOUNT
from(SELECT CONCAT(CONCAT(to_char(CFSTARTYEAR-1), '-'),substr(to_char(CFSTARTYEAR),3,2)) as FINANCIAL_YEAR,
UID_NUM as UID_NUM,AMOUNT*(CASE WHEN PENMONTHS-CFYMONTHS>12 THEN 12 ELSE PENMONTHS-CFYMONTHS end ) AS AMOUNT,
to_char(CFSTARTYEAR-1) as FULL_YEAR
from (
select distinct uid_no as UID_NUM,TYPENAME as PTYPE,amount as AMOUNT,
case when ROUND(months_between(to_date('2019-06-01','yyyy-mm-dd'),
to_date(substr(PENSION_SANCTION_DATE,1,10),'yyyy-mm-dd')),0)>0 then
ROUND(months_between(sysdate,to_date('2019-06-01','yyyy-mm-dd')),0)
else
ROUND(months_between(sysdate,to_date(substr(PENSION_SANCTION_DATE,1,10),'yyyy-mm-dd')),0)
end as PENMONTHS,
Round(case when extract(Month from sysdate)>3 then extract(Month from sysdate)-3
else 9+extract(Month from sysdate) end ,0) as CFYMONTHS,
case when extract(month from sysdate)> 3 then extract(year from sysdate)
else extract(year from sysdate)-1 end as CFSTARTYEAR
from RTGS_DEV.YSR_PENSIONS
)WHERE PENMONTHS-CFYMONTHS>0
union all
SELECT CONCAT(CONCAT(to_char(CFSTARTYEAR-2), '-'),substr(to_char(CFSTARTYEAR-1),3,2)) as FINANCIAL_YEAR,
UID_NUM as UID_NUM,AMOUNT*(CASE WHEN PENMONTHS-CFYMONTHS-12>12 THEN 12 ELSE PENMONTHS-CFYMONTHS-12 end ) AS AMOUNT,
to_char(CFSTARTYEAR-2) as FULL_YEAR
from (
select distinct uid_no as UID_NUM,TYPENAME as PTYPE,amount as AMOUNT,
case when ROUND(months_between(to_date('2019-06-01','yyyy-mm-dd'),
to_date(substr(PENSION_SANCTION_DATE,1,10),'yyyy-mm-dd')),0)>0 then
ROUND(months_between(sysdate,to_date('2019-06-01','yyyy-mm-dd')),0)
else
ROUND(months_between(sysdate,to_date(substr(PENSION_SANCTION_DATE,1,10),'yyyy-mm-dd')),0)
end as PENMONTHS,
Round(case when extract(Month from sysdate)>3 then extract(Month from sysdate)-3
else 9+extract(Month from sysdate) end ,0) as CFYMONTHS,
case when extract(month from sysdate)> 3 then extract(year from sysdate)
else extract(year from sysdate)-1 end as CFSTARTYEAR from RTGS_DEV.YSR_PENSIONS)
