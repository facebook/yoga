import {Record} from 'immutable';
import type {RecordOf} from 'immutable';

export type PositionRecordT = RecordOf<{
  top: string,
  right: string,
  bottom: string,
  left: string,
}>;

const r: PositionRecordT = Record({
  top: '',
  right: '',
  bottom: '',
  left: '',
});

export default r;
