#Red Black Tree - Event Counter
<br>Implement an event counter using red-black tree. </br>
Each event has two fields: ID and count, where count is the number of active events with the given ID. The event counter stores only those ID’s whose count is > 0. Once a count drops below 1, that ID is removed.
This counter supports the following operations in the specified time complexity.

<table class="tg" style="undefined;table-layout: fixed; width: 1000px">
<colgroup>
<col style="width: 100px">
<col style="width: 481px">
<col style="width: 127px">
</colgroup>
  <tr>
    <th style="width: 500px">Command</th>
    <th class="tg-e3zv">Desctiption</th>
    <th class="tg-e3zv">Time complexity</th>
  </tr>
  <tr>
    <td class="tg-031e">Increase(theID, m)</td>
    <td class="tg-031e">Increase the count of the event theID by m. If<br>theID is not present, insert it. Print the count<br>of theID after the addition.</td>
    <td class="tg-031e">O(log n)</td>
  </tr>
  <tr>
    <td class="tg-031e">Reduce(theID, m)</td>
    <td class="tg-031e">Decrease the count of theID by m. If theID’s<br>count becomes less than or equal to 0, remove<br>theID from the counter. Print the count of<br>theID after the deletion, or 0 if theID is<br>removed or not present.</td>
    <td class="tg-031e">O(log n)</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Count(theID)</td>
    <td class="tg-yw4l">Print the count of theID. If not present, print<br>0.</td>
    <td class="tg-yw4l">O(log n)</td>
  </tr>
  <tr>
    <td class="tg-yw4l">InRange(ID1, ID2)</td>
    <td class="tg-yw4l">Print the total count for IDs between ID1 and<br>ID2 inclusively. Note, ID1 ≤ ID2</td>
    <td class="tg-yw4l">O(log n + s) where<br>s is the number of<br>IDs in the range.</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Next(theID)</td>
    <td class="tg-yw4l">Print the ID and the count of the event with<br>the lowest ID that is greater that theID. Print<br>“0 0”, if there is no next ID.</td>
    <td class="tg-yw4l">O(log n)</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Previous(theID)</td>
    <td class="tg-yw4l">Print the ID and the count of the event with<br>the greatest key that is less that theID. Print<br>“0 0”, if there is no previous ID.</td>
    <td class="tg-yw4l">O(log n)</td>
  </tr>
</table>
