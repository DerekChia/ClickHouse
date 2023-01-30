-- Tags: no-parallel-replicas

SELECT URL AS `ym:ah:URL`, sum((NOT DontCountHits AND NOT Refresh)), quantilesTimingIf(0.1, 0.5, 0.9)((DOMCompleteTiming + LoadEventEndTiming), DOMCompleteTiming != -1 AND LoadEventEndTiming != -1) as t FROM remote('127.0.0.{1,2}', test, hits) WHERE (CounterID = 800784) AND (((DontCountHits = 0) OR (IsNotBounce = 1)) AND (URL != ''))  GROUP BY `ym:ah:URL` WITH TOTALS   HAVING (sum((NOT DontCountHits AND NOT Refresh)) > 0) AND (count() > 0)  ORDER BY sum((NOT DontCountHits AND NOT Refresh)) DESC, URL  LIMIT 0, 1
